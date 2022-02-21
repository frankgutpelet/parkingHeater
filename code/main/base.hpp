#include <ESP8266WebServer.h>
#include <Arduino.h>

class base
{
	public:
		base (ESP8266WebServer* server);

		void Render (void);
		void SetCallback_submit (void (*callback)(void));
		void Set_version (String value);
		String Get_version ();
		void Set_tempSoll (String value);
		String Get_tempSoll ();
		void Set_tempIst (String value);
		String Get_tempIst ();
		void Set_calibrated (String value);
		String Get_calibrated ();
		void Set_timer (String value);
		String Get_timer ();
	private:
		void Submit_Callback(void);
		int  ReplaceJSVariable(int index, const char * varName, const char * value, int valLength);
		void(*submit_UserCallback)(void);
		void Replace(String var, String val);
		ESP8266WebServer* server;

		String version;
		String tempSoll;
		String tempIst;
		String calibrated;
		String timer;
};