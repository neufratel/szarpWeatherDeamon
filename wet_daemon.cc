/* 
  SZARP: SCADA software 

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
*/


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include <assert.h>
#include <signal.h>
#include <errno.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

#include <libxml/parser.h>

#ifdef LIBXML_XPATH_ENABLED

#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

#include "ipchandler.h"
#include "liblog.h"
#include "xmlutils.h"


#include "conversion.h"

#include <string>
#include <boost/tokenizer.hpp>
#include "USBConnector.h"
using std::string;

#define DAEMON_INTERVAL 10

/**
 * Modbus communication config.
 */
class WeatherDaemon {
public :
	/**
	 * @param params number of params to read
	 */
	WeatherDaemon(int params);
	~WeatherDaemon();

	/** 
	 * Parses XML 'device' element.
	 * @return - 0 on success, 1 on error 
	 */
	int ParseConfig(DaemonConfig * cfg);

	/**
	 * Tries to execute program.
	 * @param ipc IPCHandler
	 * @return 0 on success, 1 on error
	 */
	int Exec(IPCHandler *ipc, int tab[]);

	/** Wait for next cycle. */
	void Wait();
	
protected :
	/** helper function for XML parsing 
	 * @return 1 on error, 0 otherwise */
	int XMLCheckFreq(xmlXPathContextPtr xp_ctx, int dev_num);
	
	int m_single;		/**< are we in 'single' mode */
	public:
	int m_params_count;	/**< size of params array */
	protected:
	char ** m_argvp;	/**< command to execute */
	int m_freq;		/**< execute frequency */
	time_t m_last;
};

/**
 * @param params number of params to read
 * @param sends number of params to send (write)
 */
WeatherDaemon::WeatherDaemon(int params) 
{
	assert(params >= 0);

	m_params_count = params;
	m_freq = DAEMON_INTERVAL;
	m_single = 0;
	m_last = 0;
	m_argvp = NULL;
}

WeatherDaemon::~WeatherDaemon() 
{
}


int WeatherDaemon::XMLCheckFreq(xmlXPathContextPtr xp_ctx, int dev_num)
{
	char *e;
	xmlChar *c;
	long l;

	asprintf(&e, "/ipk:params/ipk:device[position()=%d]/@exec:frequency",
			dev_num);
	assert (e != NULL);
	c = uxmlXPathGetProp(BAD_CAST e, xp_ctx);
	free(e);
	if (c == NULL)
		return 0;
	l = strtol((char *)c, &e, 0);
	if ((*c == 0) || (*e != 0)) {
		sz_log(0, "incorrect value '%s' for exec:frequency, number expected",
				(char *)c);
		xmlFree(c);
		return 1;
	}
	xmlFree(c);
	if (l < DAEMON_INTERVAL) {
		sz_log(0, "value '%ld' for exec:frequency to small", l);
		return 1;
	}
	m_freq = (int)l;
	sz_log(2, "using exec frequency %d", m_freq);
	return 0;
}

int WeatherDaemon::ParseConfig(DaemonConfig * cfg)
{
	xmlDocPtr doc;
	xmlXPathContextPtr xp_ctx;
	int dev_num;
	int ret;
	
	/* get config data */
	assert (cfg != NULL);
	dev_num = cfg->GetLineNumber();
	assert (dev_num > 0);
	doc = cfg->GetXMLDoc();
	assert (doc != NULL);

	/* prepare xpath */
	xp_ctx = xmlXPathNewContext(doc);
	assert (xp_ctx != NULL);

	ret = xmlXPathRegisterNs(xp_ctx, BAD_CAST "ipk",
			SC::S2U(IPK_NAMESPACE_STRING).c_str());
	assert (ret == 0);
	ret = xmlXPathRegisterNs(xp_ctx, BAD_CAST "exec",
			BAD_CAST IPKEXTRA_NAMESPACE_STRING);
	assert (ret == 0);

	if (XMLCheckFreq(xp_ctx, dev_num))
		return 1;

	xmlXPathFreeContext(xp_ctx);
	
	m_single = cfg->GetSingle();
	
	std::wstring path = cfg->GetDevice()->GetPath();
	std::wstring options = cfg->GetDevice()->GetOptions();
	if (m_single) {
		printf("Using command '%s'\n", SC::S2A(path + L" " + options).c_str());
	}

	using namespace boost;
        typedef escaped_list_separator<wchar_t, std::char_traits<wchar_t> > wide_sep;
        typedef tokenizer<wide_sep, std::wstring::const_iterator, std::wstring> wide_tokenizer;
        wide_sep esp(L"\\", L" ", L"\"'");
        wide_tokenizer tok(options, esp);
        std::vector<char *> argv_v;
        for (wide_tokenizer::iterator i = tok.begin(); i != tok.end(); i++) {
                argv_v.push_back(strdup(SC::S2A(*i).c_str()));
        }
        m_argvp = (char **) malloc(sizeof(char *) * argv_v.size() + 2);
        m_argvp[0] = strdup(SC::S2A(path).c_str());
        int j = 1;
        for (std::vector<char *>::iterator i = argv_v.begin(); i != argv_v.end(); i++, j++) {
                m_argvp[j] = *i;
        }
        m_argvp[j] = NULL;

	return 0;
}


void WeatherDaemon::Wait() 
{
	time_t t;
	t = time(NULL);
	
	
	if (t - m_last < m_freq) {
		int i = m_freq - (t - m_last);
		while (i > 0) {
			i = sleep(i);
		}
	}
	m_last = time(NULL);
	return;
}

int WeatherDaemon::Exec(IPCHandler *ipc, int tab[])
{
	

	for (int i = 0; i < m_params_count; i++) {
		ipc->m_read[i] = SZARP_NO_DATA;
	}
	
	for (int i = 0; i < m_params_count ; ++i )
	{
		ipc->m_read[i] = tab[i];
	
	}

	
	
	return 0;
}

RETSIGTYPE terminate_handler(int signum)
{
	sz_log(2, "signal %d caught, exiting", signum);
	signal(signum, SIG_DFL);
	raise(signum);
}

void init_signals()
{
	int ret;
	struct sigaction sa;
	sigset_t block_mask;

	sigfillset(&block_mask);
	sigdelset(&block_mask, SIGKILL);
	sigdelset(&block_mask, SIGSTOP);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = terminate_handler;
	ret = sigaction(SIGTERM, &sa, NULL);
	assert (ret == 0);
	ret = sigaction(SIGINT, &sa, NULL);
	assert (ret == 0);
	ret = sigaction(SIGHUP, &sa, NULL);
	assert (ret == 0);
}

int main(int argc, char *argv[])
{
	DaemonConfig   *cfg;
	IPCHandler     *ipc;
	WeatherDaemon *dmn;
	WeatherStation * station;
	station= new WeatherStation();
	int station_data[10];
	station->readStation(station_data, 10);

	xmlInitParser();
	LIBXML_TEST_VERSION
	xmlLineNumbersDefault(1);

	cfg = new DaemonConfig("wetdmn");
	assert (cfg != NULL);
	
	if (cfg->Load(&argc, argv))
		return 1;
	
	dmn = new WeatherDaemon(cfg->GetDevice()->GetFirstRadio()->
			GetFirstUnit()->GetParamsCount());
	assert (dmn != NULL);
	
	if (dmn->ParseConfig(cfg)) {
		return 1;
	}

	ipc = new IPCHandler(cfg);
	if (!cfg->GetSingle()) {
		if (ipc->Init())
			return 1;
	}

	init_signals();

	sz_log(2, "Starting WetDaemon");
	

	while (true) {
		dmn->Wait();
		station->readStation(station_data, 10);
		dmn->Exec(ipc, station_data);
		/* send data from parcook segment */
		ipc->GoParcook();
	}
	return 0;
}

#else /* LIBXML_XPATH_ENABLED */

int main(void)
{
	printf("libxml2 XPath support not enabled!\n");
	return 1;
}

#endif /* LIBXML_XPATH_ENABLED */

