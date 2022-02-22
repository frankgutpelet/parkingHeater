#include "base.hpp"
#include <ArduinoJson.h>

StaticJsonDocument < 300 > doc;
char base_text[] = "﻿<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n\
<html xmlns=\"http://www.w3.org/1999/xhtml\">\n\
\n\
<head>\n\
	<link rel=\"stylesheet\" style=\"text/css\" href=\"/style.css\">\n\
<meta content=\"de\" http-equiv=\"Content-Language\" />\n\
<meta content=\"text/html; charset=utf-8\" http-equiv=\"Content-Type\" />\n\
<title>Viano Standheizung</title>\n\
<style type=\"text/css\">\n\
\n\
\n\
html {\n\
  background: linear-gradient(to bottom right, navy, black);\n\
 	background-repeat: no-repeat;\n\
 	min-height: 100%;\n\
}\n\
body {\n\
\n\
}\n\
\n\
.button {\n\
  display: inline-block;\n\
  padding: 15px 25px;\n\
  font-size: 24px;\n\
  cursor: pointer;\n\
  text-align: center;\n\
  text-decoration: none;\n\
  outline: none;\n\
  color: #fff;\n\
  background-color: silver;\n\
  border: none;\n\
  border-radius: 10px;\n\
  box-shadow: 0 9px darkblue;\n\
}\n\
.button2 {\n\
  display: inline-block;\n\
  padding: 30px 45px;\n\
  font-size: 35px;\n\
  cursor: pointer;\n\
  text-align: center;\n\
  text-decoration: none;\n\
  outline: none;\n\
  color: #fff;\n\
  background-color: silver;\n\
  border: none;\n\
  border-radius: 10px;\n\
  box-shadow: 0 9px darkblue;\n\
}\n\
.button:hover {\n\
	background-color: blueviolet\n\
}\n\
\n\
.button:active {\n\
  background-color: #3e8e41;\n\
  box-shadow: 0 5px #666;\n\
  transform: translateY(4px);\n\
}\n\
.auto-style-headline {\n\
    text-transform: uppercase;\n\
    font-family: verdana;\n\
    font-size: 3em;\n\
    font-weight: 700;\n\
    color: #f5f5f5;\n\
    text-shadow: 1px 1px 1px #919191,\n\
        1px 1px 1px #919191,\n\
        1px 2px 1px #919191,\n\
        1px 3px 1px #919191,\n\
        1px 4px 1px #919191,\n\
        1px 5px 1px #919191,\n\
\n\
    1px 18px 6px rgba(16,16,16,0.4),\n\
    1px 22px 10px rgba(16,16,16,0.2),\n\
    1px 25px 35px rgba(16,16,16,0.2);\n\
}\n\
\n\
.auto-style1 {\n\
	font-family: \"Gill Sans\", \"Gill Sans MT\", Calibri, \"Trebuchet MS\", sans-serif;\n\
	font-size: xx-large;\n\
	color: #FFFFFF;\n\
}\n\
.auto-style2 {\n\
    font-family: verdana;\n\
    font-size: 1em;\n\
    font-weight: 700;\n\
    color: #f5f5f5;\n\
    text-shadow: 1px 1px 1px #919191,\n\
    1px 5px 3px rgba(16,16,16,0.4),\n\
    1px 10px 5px rgba(16,16,16,0.2);\n\
}\n\
.auto-style-version {\n\
	text-align: right;\n\
	text-align: top;\n\
    font-family: verdana;\n\
    font-size: 0.6em;\n\
    font-weight: 700;\n\
    color: #f5f5f5;\n\
    text-shadow: 1px 1px 1px #919191,\n\
    1px 2px 1px rgba(16,16,16,0.4),\n\
    1px 4px 2px rgba(16,16,16,0.2);\n\
}\n\
.auto-style3 {\n\
	color: #FF0000;\n\
}\n\
.auto-style3 {\n\
	border-style: solid;\n\
	border-width: 1px;\n\
}\n\
.slider {\n\
  -webkit-appearance: none;\n\
  width: 100%;\n\
  height: 35px;\n\
  background: #silver;\n\
  outline: none;\n\
  opacity: 0.7;\n\
  -webkit-transition: .2s;\n\
  transition: opacity .2s;\n\
}\n\
.slider::-webkit-slider-thumb {\n\
  -webkit-appearance: none;\n\
  appearance: none;\n\
  width: 50px;\n\
  height: 35px;\n\
  background: darkblue;\n\
  cursor: pointer;\n\
}\n\
#CalibrationProgress {\n\
  width: 50%;\n\
  background-color: grey;\n\
  bottom: 20%;\n\
  position: fixed;\n\
  float: right;\n\
  visible: false;\n\
  box-shadow: 8px 8px 5px #444;\n\
}\n\
\n\
#CalibrationBar {\n\
  width: 1%;\n\
  height: 30px;\n\
  background-color: green;\n\
}\n\
\n\
.dotOn {\n\
  height: 25px;\n\
  width: 25px;\n\
  background-color: #f00;\n\
  border-radius: 50%;\n\
  display: inline-block;\n\
}\n\
.dotOff {\n\
  height: 25px;\n\
  width: 25px;\n\
  background-color: #bbb;\n\
  border-radius: 50%;\n\
  display: inline-block;\n\
}\n\
\n\
</style>\n\
</head>\n\
<body>\n\
<p id=\"version\" class=\"auto-style-version\">Version: ?</p>\n\
<p class=\"auto-style-headline\" align=\"center\">Standheizung</p>\n\
<table class=\"auto-style3\" style=\"width: 100%\">\n\
	<tr>\n\
		<td class=\"auto-style2\" style=\"width: 484px\"><strong>Temperatur (Ist)</strong></td>\n\
		<td class=\"auto-style2\"><strong id=\"tempIst\"></strong></td>\n\
	</tr>\n\
	<tr>\n\
		<td class=\"auto-style2\" style=\"width: 484px\"><strong>Temperatur (Soll)</strong></td>\n\
		<td class=\"auto-style2\"><strong id=\"tempSoll\"></strong></td>\n\
	</tr>\n\
	<tr>\n\
		<td class=\"auto-style2\" style=\"width: 484px\"><strong>Timer</strong></td>\n\
		<td id=\"timerColumn\" class=\"auto-style2\"><strong id=\"timer\"></strong></td>\n\
	</tr>\n\
	<tr>\n\
		<td class=\"auto-style2\" style=\"width: 484px\"><strong>Turbo</strong></td>\n\
		<td id=\"timerColumn\" class=\"auto-style2\"><strong id=\"turbo\"></strong></td>\n\
	</tr>\n\
	<tr>\n\
		<td class=\"auto-style2\" style=\"width: 484px\"><strong>Status</strong></td>\n\
		<td id=\"timerColumn\" class=\"auto-style2\"><strong id=\"state\"></strong><td><span id=\"burn\" class=\"dotOff\"></span></td><td><span id=\"burnTurbo\" class=\"dotOff\"></span></td>\n\
	</tr>\n\
</table>\n\
</p>\n\
\n\
<table  class=\"auto-style3\" style=\"width: 100%\">\n\
	<tr>\n\
		 <p class=\"auto-style2\">Timer:</p>\n\
		<div class=\"slidecontainer\">\n\
			<input id=\"slider\" type=\"range\" min=\"1\" max=\"90\" value={{ timer }} class=\"slider\" id=\"timer\" onchange=\"sliderChange()\">\n\
		</div>\n\
		</p>\n\
	</tr>\n\
</table>\n\
</p>\n\
<table  class=\"auto-style3\" style=\"width: 100%\">\n\
	<tr>\n\
		<p class=\"auto-style2\">Temperatur:</p>\n\
		<div class=\"slidecontainer\">\n\
			<input id=\"slider2\" type=\"range\" min=\"20\" max=\"60\" value={{ timer }} class=\"slider\" id=\"temp\" onchange=\"slider2Change()\">\n\
		</div>\n\
		</p>\n\
	</tr>\n\
</table>\n\
</p>\n\
<table style=\"width: 100%\">\n\
	<tr>\n\
		<td>\n\
			<form action=\"submit\" method=\"post\" >\n\
				<button class=\"button2\" id=\"submitBtn\" type=\"submit\" name=\"action\" value=\"\" >übernehmen</button>\n\
			</form>\n\
		</td>\n\
		<td>\n\
			<form action=\"submit\" method=\"get\" >\n\
				<a href=\"http://standheizung\" class=\"button2\" >neu laden</a>\n\
			</form>\n\
		</td>\n\
		<td>\n\
			<form action=\"submit\" method=\"get\" >\n\
				<p class=\"button2\" type=\"submit\" onclick=\"turbo()\">Turbo</p>\n\
			</form>\n\
		</td>\n\
	</tr>\n\
</table>\n\
\n\
\n\
</body>\n\
\n\
</html>\n\
<script>\n\
\n\
	var values = {\n\
		\"timer\" : \"0\",              \n\
		\"tempIst\" : \"0\",            \n\
		\"tempSoll\" : \"0\",           \n\
		\"calibrated\" : \"0\",         \n\
		\"version\" : \"0\",            \n\
		\"state\" : \"OFF\",            \n\
		\"heating\" : \"ON\",           \n\
		\"turbo\" : \"OFF\"}            \n\
\n\
	if (values.heating == \"ON\")\n\
	{\n\
		document.getElementById(\"burn\").classList.add(\"dotOn\")\n\
		document.getElementById(\"burn\").classList.remove(\"dotOff\")\n\
		if (\"ON\" == values.turbo)\n\
		{\n\
			document.getElementById(\"burnTurbo\").classList.add(\"dotOn\")\n\
			document.getElementById(\"burnTurbo\").classList.remove(\"dotOff\")\n\
		}\n\
		else\n\
		{\n\
			document.getElementById(\"burnTurbo\").classList.add(\"dotOff\")\n\
			document.getElementById(\"burnTurbo\").classList.remove(\"dotOn\")\n\
		}\n\
	}\n\
	else\n\
	{\n\
		document.getElementById(\"burn\").classList.add(\"dotOff\")\n\
		document.getElementById(\"burn\").classList.remove(\"dotOn\")\n\
		document.getElementById(\"burnTurbo\").classList.add(\"dotOff\")\n\
		document.getElementById(\"burnTurbo\").classList.remove(\"dotOn\")\n\
\n\
	}\n\
\n\
	if (values.timer >= 61)\n\
	{\n\
		document.getElementById(\"timer\").innerHTML = \"Dauer\"\n\
	}\n\
	else\n\
	{\n\
		document.getElementById(\"timer\").innerHTML = values.timer + \"min\"\n\
	}\n\
\n\
	document.getElementById(\"version\").innerHTML = \"Version: \" + values.version\n\
		\n\
\n\
	document.getElementById(\"slider\").value = values.timer\n\
	document.getElementById(\"slider2\").value = values.tempSoll * 2\n\
	document.getElementById(\"tempIst\").innerHTML = values.tempIst + \"°C\"\n\
	document.getElementById(\"tempSoll\").innerHTML = values.tempSoll + \"°C\"\n\
	document.getElementById(\"state\").innerHTML = values.state\n\
	document.getElementById(\"turbo\").innerHTML = values.turbo\n\
	document.getElementById(\"submitBtn\").value = JSON.stringify(values)\n\
\n\
	function turbo()\n\
	{\n\
		if(\"OFF\" == values.turbo)\n\
		{\n\
			values.turbo = \"ON\"\n\
		}\n\
		else\n\
		{\n\
			values.turbo = \"OFF\"\n\
		}\n\
		document.getElementById(\"turbo\").innerHTML = values.turbo + \" (übernehmen)\"\n\
		document.getElementById(\"submitBtn\").value = JSON.stringify(values)\n\
	}\n\
	function sliderChange()\n\
	{\n\
\n\
		values.timer = Math.round(document.getElementById(\"slider\").value)\n\
		if (values.timer > 60)\n\
		{\n\
			values.timer = 61\n\
			document.getElementById(\"timer\").innerHTML = \"Dauer (übernehmen)\"\n\
			document.getElementById(\"submitBtn\").value = JSON.stringify(values)\n\
		}\n\
		else\n\
		{\n\
			document.getElementById(\"timer\").innerHTML = values.timer + \"min (übernehmen)\"\n\
			document.getElementById(\"submitBtn\").value = JSON.stringify(values)\n\
		}\n\
	}\n\
	function slider2Change()\n\
	{\n\
		values.tempSoll = document.getElementById(\"slider2\").value/2\n\
		document.getElementById(\"tempSoll\").innerHTML = values.tempSoll + \"°C (übernehmen)\"\n\
		document.getElementById(\"submitBtn\").value = JSON.stringify(values)\n\
\n\
	}\n\
\n\
</script>";

base::base(ESP8266WebServer* server)
{
	this->server = server;
	this->submit_UserCallback = (void(*)()) NULL;
	this->server->on("/submit", std::bind( & base::Submit_Callback, this));
}
void base::Submit_Callback(void)
{
	String jsonstring = this->server->arg("action");
	DeserializationError error = deserializeJson(doc, jsonstring);
	Serial.println(jsonstring);
	JsonObject obj = doc.as < JsonObject > ();

	if (error)
	{
	Serial.print(F("deserializeJson() failed: "));
	Serial.println(error.f_str());
	}
	else
	{
		this->timer = obj["timer"].as < String > ();
		this->tempIst = obj["tempIst"].as < String > ();
		this->tempSoll = obj["tempSoll"].as < String > ();
		this->heating = obj["heating"].as < String > ();
		this->turbo = obj["turbo"].as < String > ();
		this->version = obj["version"].as < String > ();
		this->state = obj["state"].as < String > ();
		this->calibrated = obj["calibrated"].as < String > ();

	}
	if (NULL != this->submit_UserCallback)
	{
		this->submit_UserCallback();
	}
}

void base::SetCallback_submit (void (*callback)(void))
{
	this->submit_UserCallback = callback;
}

void base::Set_timer (String value)
{
	this->timer = value;
	this->Replace("timer", this->timer);
}

String base::Get_timer ( void )
{
	return this->timer;
}
void base::Set_tempIst (String value)
{
	this->tempIst = value;
	this->Replace("tempIst", this->tempIst);
}

String base::Get_tempIst ( void )
{
	return this->tempIst;
}
void base::Set_tempSoll (String value)
{
	this->tempSoll = value;
	this->Replace("tempSoll", this->tempSoll);
}

String base::Get_tempSoll ( void )
{
	return this->tempSoll;
}
void base::Set_heating (String value)
{
	this->heating = value;
	this->Replace("heating", this->heating);
}

String base::Get_heating ( void )
{
	return this->heating;
}
void base::Set_turbo (String value)
{
	this->turbo = value;
	this->Replace("turbo", this->turbo);
}

String base::Get_turbo ( void )
{
	return this->turbo;
}
void base::Set_version (String value)
{
	this->version = value;
	this->Replace("version", this->version);
}

String base::Get_version ( void )
{
	return this->version;
}
void base::Set_state (String value)
{
	this->state = value;
	this->Replace("state", this->state);
}

String base::Get_state ( void )
{
	return this->state;
}
void base::Set_calibrated (String value)
{
	this->calibrated = value;
	this->Replace("calibrated", this->calibrated);
}

String base::Get_calibrated ( void )
{
	return this->calibrated;
}
void base::Render( void )
{
	this->server->send( 200, base_text );
}
void base::Replace(String var, String val)
{
	int varLength = var.length() + 1;
	int valLength = val.length() + 1;
	char varName[varLength];
	char value[valLength];
	char tmpVarName[varLength];
	if (10 < valLength)
	{
		valLength = 10;
	}
	var.toCharArray(varName, varLength);
	val.toCharArray(value, valLength);
#ifdef DEBUG
	 Serial.println("Search for " + var + ");
#endif
	for (int i=0; i < sizeof(base_text); i++)
	{
		if ('\n' == base_text[i-1])
		{
			memcpy(tmpVarName, & base_text[i+3], varLength);
			tmpVarName[varLength - 1] = '\0';
			if ((0 == strcmp(varName, tmpVarName)) && ('\"' == base_text[i+2]) && ('\"' == base_text[i+2+varLength]))
			{
				/* replace variable and set iterator to end of line */
				i = this->ReplaceJSVariable((i+7+varLength), varName, value, valLength);
			}
		}
	}
}
int base::ReplaceJSVariable(int index, const char * varName, const char * value, int valLength)
{
	char lastChar = ' ';
	int endOfLine = index;
#ifdef DEBUG
	Serial.println(String("Found variable: ") + varName + " first char: " + base_text[index]);
#endif


	/*delete value in line */
	do
	{
		if (' ' != base_text[endOfLine])
		{
			lastChar = base_text[endOfLine];
		}
		base_text[endOfLine] = ' ';
		endOfLine ++;
	}while (base_text[endOfLine] != '\n');
#ifdef DEBUG
	Serial.println("Value deleted");
#endif
	memcpy( &base_text[index], value, (valLength - 1));
	base_text[(index + valLength - 1)] = '\"';
	base_text[(index + valLength)] = lastChar;
	return endOfLine;
}
