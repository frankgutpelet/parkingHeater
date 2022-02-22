#include <ESP8266WebServer.h>
#include <Arduino.h>

class base
{
	public:
		base (ESP8266WebServer* server);

		void Render (void);
		void SetCallback_submit (void (*callback)(void));
		void Set_timer (String value);
		String Get_timer ();
		void Set_tempIst (String value);
		String Get_tempIst ();
		void Set_tempSoll (String value);
		String Get_tempSoll ();
		void Set_heating (String value);
		String Get_heating ();
		void Set_turbo (String value);
		String Get_turbo ();
		void Set_version (String value);
		String Get_version ();
		void Set_state (String value);
		String Get_state ();
		void Set_calibrated (String value);
		String Get_calibrated ();
	private:
		void Submit_Callback(void);
		int  ReplaceJSVariable(int index, const char * varName, const char * value, int valLength);
		void(*submit_UserCallback)(void);
		void Replace(String var, String val);
		ESP8266WebServer* server;

		String timer;
		String tempIst;
		String tempSoll;
		String heating;
		String turbo;
		String version;
		String state;
		String calibrated;
};
