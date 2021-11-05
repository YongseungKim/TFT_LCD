#include "Arduino.h"

class SendMessage{
private:
    String _http_message;
    String _box_no;
    String _password;
    String _mail_no;
    String _mail_type;
    String _name;
    String _bat_usage;

public:
    SendMessage(){
        _http_message = "https://yongseung.pythonanywhere.com/mail/reg/?";
        _box_no = "";
        _password = "";
        _mail_no = "";
        _mail_type = "";
        _name = "";
        _bat_usage = "";
    }


public:

    String getMessage(){ 
        return _http_message; 
    }

    String getBoxNo(){ return _box_no;}
    void setBoxNo(String box_no){ _box_no = box_no; }

    String getPassword(){ return _password;}    
    void setPassword(String password){ _password = password; }

    String getMailNo(){ return _mail_no;}    
    void setMailNo(String mail_no){ _mail_no = mail_no; }

    String getMailType(){ return _mail_type;}    
    void setMailType(String mail_type){ _mail_type = mail_type; }

    String getName(){ return _name;}    
    void setName(String name){ _name = name; }

    String getBatUsage(){ return _bat_usage;}    
    void setBatUsage(String bat_usage){ _bat_usage = bat_usage; }

    void makeSendmessage(){
        _http_message = _http_message + "b:" + _box_no + "pw:" + _password;
        if(_mail_no != "") _http_message = _http_message + ":" + _mail_no;
        if(_mail_type != "") _http_message = _http_message + "pt" + _mail_type;
        if( _name != "") _http_message = _http_message + "n" + _name;
        if( _bat_usage != "") _http_message = _http_message + "u" + _bat_usage;
    }

    //"https://yongseung.pythonanywhere.com/mail/reg/?b=A002-001B&p=0001&m=123456&n=홍길동";
    void makeSendmessagOld(){
        _http_message = _http_message + "b=" + _box_no + "&" + "p=" + _password;
        if(_mail_no != "") _http_message = _http_message + "&" +  "m=" + _mail_no;
        if( _name != "") _http_message = _http_message + "&" +  "n=" + _name;
    }

    void print(){
        Serial.println(_http_message);
    }
};

