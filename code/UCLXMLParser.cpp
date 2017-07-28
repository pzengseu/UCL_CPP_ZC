/*
 * xmltest.cpp
 *
 *  Created on: 2017-7-22
 *      Author: Administrator
 */

#include "./header_file/XMLTools.h"
#include "./header_file/UCLFormatMap.h"
#include <stdio.h>
#include <inttypes.h>




void readXml(const char* filePath) {
//______________________________________________________________________
// Read information from xml file.

// define xml file path, as follow , we use relative path,
// but you can use absolute path also.
	TiXmlDocument doc(filePath);
	bool loadOkay = doc.LoadFile();
	// faile to load 'phonebookdata.xml'.
	if (!loadOkay) {
	    printf( "Could not load test file %s. Error='%s'. Exiting.\n", filePath,doc.ErrorDesc() );
	    exit( 1 );
	}
	TiXmlElement* root = doc.RootElement();


// get dom root of 'phonebookdata.xml', here root should be 'phonebook'.


printf("_______________________________________\n\n");
printf("     contacted person information      \n\n");
// trace every items below root.
for( TiXmlNode*  item = root->FirstChild( "item" );
         item;
         item = item->NextSibling( "item" ) ) {
    printf("_______________________________________\n");

    // read name.
    TiXmlNode* child = item->FirstChild();
    const char* name = child->ToElement()->GetText();
    if (name) {
        printf("name:%s\n",name);
    } else {
        printf("name:\n");
    }

    // read address.
    child = item->IterateChildren(child);
    const char* addr = child->ToElement()->GetText();
    if (addr) {
        printf("addr:%s\n",addr);
    } else {
        printf("addr:\n");
    }


    // read telephone no.
    child = item->IterateChildren(child);
    const char* tel = child->ToElement()->GetText();
        if (tel) {
        printf("tel:%s\n",tel);
    } else {
        printf("tel:\n");
    }

    // read e-mail.
    child = item->IterateChildren(child);
    const char* email = child->ToElement()->GetText();
    if(email) {
        printf("email:%s\n",email);
    } else {
        printf("email:\n");
    }

    printf("\n");

}
//______________________________________________________________________
}


void writeXml(const char* filePath) {
	TiXmlDocument doc(filePath);
	bool loadOkay = doc.LoadFile();
	// faile to load 'phonebookdata.xml'.
	if (!loadOkay) {
	    printf( "Could not load test file %s. Error='%s'. Exiting.\n", filePath,doc.ErrorDesc() );
	    exit( 1 );
	}

//______________________________________________________________________
// Add information to xml file and save it.
TiXmlElement* writeRoot = doc.RootElement();
TiXmlNode* newNode = new TiXmlElement("item");

   const TiXmlNode* name4NewNode = new TiXmlElement("name");
newNode->InsertEndChild(*name4NewNode)->InsertEndChild(TiXmlText("pipi"));

const TiXmlNode* addr4NewNode = new TiXmlElement("addr");
newNode->InsertEndChild(*addr4NewNode)->InsertEndChild(TiXmlText("Shaanxi Xianyang"));

const TiXmlNode* tel4NewNode = new TiXmlElement("tel");
newNode->InsertEndChild(*tel4NewNode)->InsertEndChild(TiXmlText("02937310627"));

const TiXmlNode* email4NewNode = new TiXmlElement("email");
newNode->InsertEndChild(*email4NewNode)->InsertEndChild(TiXmlText("pipi@home.com"));

writeRoot->InsertEndChild(*newNode);
doc.SaveFile();
}


void readUCLXml(const char* filePath) {
//______________________________________________________________________
// Read information from xml file.
// define xml file path, as follow , we use relative path,
// but you can use absolute path also.
    TiXmlDocument doc(filePath);
    bool loadOkay = doc.LoadFile();
    // faile to load the xml file.
    if (!loadOkay) {
        printf( "Could not load test file %s. Error='%s'. Exiting.\n", filePath,doc.ErrorDesc() );
        exit( 1 );
    }
    TiXmlElement* root = doc.RootElement();

    TiXmlNode*  item11 = root->FirstChild( "version" );
    printf("ttt:%s\n", item11->FirstChild("v2")->ToElement()->GetText());
    TiXmlNode*  item22 = root->FirstChild( "secuenerlevecode" );
    printf("sss:%s\n", item22->FirstChild("s1")->ToElement()->GetText());

    char buff[20];
    sprintf(buff, "%s%d", VERSION_INITIAL, 3);
    printf("%s\n", buff);
    TiXmlNode*  item00 = root->FirstChild( VERSION_NAME );
    printf("con:%s\n", item00->FirstChild(buff)->ToElement()->GetText());
    printf("_______________________________________\n\n");

}

void category(const UCLCode &code) {

    const char* filePath = "./zc_conf_xml/zcCategoryConf.xml";
    TiXmlDocument doc(filePath);
    bool loadOkay = doc.LoadFile();
    // faile to load the xml file.
    if (!loadOkay) {
        printf( "Could not load xml file %s. Error='%s'. Exiting.\n", filePath,doc.ErrorDesc() );
        exit( 1 );
    }
    TiXmlElement* root = doc.RootElement();
    const int buffSize = 20;
    int width = 32;
    char buff[buffSize];


    TiXmlNode*  item = root->FirstChild( VERSION_NAME );
    sprintf(buff, "%s%llu", VERSION_INITIAL, code.getVersion());
    cout << setfill(' ') << setw(width) << "Version:" << item->FirstChild(buff)->ToElement()->GetText() << endl;

    item = root->FirstChild( CATEGORY_NAME );
    memset(buff, 0, sizeof(char)*buffSize);
    sprintf(buff, "%s%llu", CATEGORY_INITIAL, code.getCategory());
    cout << buff << endl;
    cout << setfill(' ') << setw(width) << "Version:" << item->FirstChild(buff)->ToElement()->GetText() << endl;
}

/**
 * fieldName: the name of the field:
 * mbuOrder: the order of the mbu in the field
 * mbuValue: the value of mbu
 * show the value of the mbu from xml file
 */
void showMBUFromXml(const char* fieldName, uint8_t mbuOrder, uint64_t mbuValue) {

//cout << ">>>>>>>>>>MBU" << endl;

// Read information from xml file.
// define xml file path, as follow , we use relative path,
// but you can use absolute path also.
    const char* filePath = "./zc_conf_xml/zcConf.xml";
    const char* tiXmlNodeUndefined = "Undefined";
    TiXmlDocument doc(filePath);
    bool loadOkay = doc.LoadFile();
    // failed to load the xml file.
    if (!loadOkay) {
        printf( "Could not load xml file %s. Error='%s'. Exiting.\n", filePath,doc.ErrorDesc() );
        exit( 1 );
    }
    TiXmlElement* root = doc.RootElement();

    const int buffSize = 64;
    int width = 32;
    char buff[buffSize];
    memset(buff, 0, sizeof(char)*buffSize);

    char buffFieldName[buffSize];
    memset(buffFieldName, 0, sizeof(char)*buffSize);

    sprintf(buff, "%s_NAME", fieldName);
	if(CODE_NAME.find(buff) == CODE_NAME.end()) {
		cout << buff << " is not in CODE_NAME!!!" << endl;
		exit(1);
	} else {
		strcpy(buffFieldName, CODE_NAME.find(buff)->second.c_str());
	}

//cout << 	"aaaaa: " << buffFieldName << endl;
    TiXmlNode*  item = root->FirstChild( buffFieldName );
    if(item == NULL)  {
    	cout << "Node is not in xml file" << endl;
    	exit(1);
    }

    memset(buffFieldName, 0, sizeof(char)*buffSize);
    memset(buff, 0, sizeof(char)*buffSize);
    sprintf(buff, "%s_INITIAL", fieldName);
	if(CODE_NAME.find(buff) == CODE_NAME.end()) {
		cout << buff << " is not in CODE_NAME!!!" << endl;
		exit(1);
	} else {
		strcpy(buffFieldName, CODE_NAME.find(buff)->second.c_str());
	}

    memset(buff, 0, sizeof(char)*buffSize);
    sprintf(buff, "%s_%u_%llu", buffFieldName, mbuOrder, mbuValue);
    TiXmlNode* pTXNode = item->FirstChild(buff);
    cout << setfill(' ') << setw(width) << fieldName << " : ";
    if(pTXNode != NULL) {
    	cout << pTXNode ->ToElement()->GetText() << "\n";
    } else {
    	cout << tiXmlNodeUndefined << "\n";
    }
//cout << "MBU>>>>>>>>" << endl;
}

/**
 * fieldName: the name of the field
 * code: the reference of an UCLCode object
 * return the value from xml file of the given field
 */
void showFieldFromXML(const char* fieldName, const UCLCode &code) {
//cout << "=====\n";
	uint64_t* fieldArr = NULL;
	fieldArr = code.getField(fieldName);
//cout << "arr=====\n";
	for(int i = 1; i < fieldArr[0]; ++i) {
		showMBUFromXml(fieldName, i, fieldArr[i]);
//cout << "arr: " << fieldArr[i] << "\n";
	}
//cout << "arr=====" << endl;
	delete fieldArr;
}

void showCodeFromXML(const UCLCode &code) {
    int width = 32;
cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	showFieldFromXML("VERSION", code);
	showFieldFromXML("TYPEOFMEDIA", code);
	showFieldFromXML("PRIOANDPOLI", code);
	showFieldFromXML("FLAG", code);
	cout << setfill(' ') << setw(width) << "PARSERULE" << " : " << code.getParseRule() << "\n";
	//showFieldFromXML("PARSERULE", code);
	showFieldFromXML("SOUROFCONT", code);
	showFieldFromXML("CATEGORY", code);
	cout << setfill(' ') << setw(width) << "SUBCATEGORY" << " : " << code.getSubCategory() << "\n";
	//showFieldFromXML("SUBCATEGORY", code);
	showFieldFromXML("TOPIC", code);
	showFieldFromXML("COPYANDTYPEOFCONT", code);
	showFieldFromXML("SECUENERLEVECODE", code);
	showFieldFromXML("LANGUAGE", code);
	showFieldFromXML("SIZEOFCONTENT", code);

	const time_t t = code.getTimeStamp();
	cout << setfill(' ') << setw(width) << "TIMESTAMP" << " : " << t << "\t";
	struct tm* st = localtime(&t);
	cout << setfill(' ') << setw(width) << "TIME" << " : "
			<< st->tm_year + 1900 << "-"
			<< st->tm_mon + 1 << "-"
			<< st->tm_mday << " "
			<< st->tm_hour << ":"
			<< st->tm_min << ":"
			<< st->tm_sec
			<< "\n";

	cout << setfill(' ') << setw(width) << "SERIALNUMBER" << " : " << code.getSerialNumber() << "\n";
	cout << setfill(' ') << setw(width) << "MULTIPLEXBYTES" << " : " << code.getMultiplexBytes() << "\n";
	cout << setfill(' ') << setw(width) << "CODECHECK" << " : " << code.getCodeCheck() << "\n";
cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
}

void showFromXml(const UCLCode &code) {
	showFieldFromXML("PRIOANDPOLI", code);

// Read information from xml file.
// define xml file path, as follow , we use relative path,
// but you can use absolute path also.
    const char* filePath = "./zc_conf_xml/zcConf.xml";
    const char* tiXmlNodeUndefined = "Undefined";
    TiXmlDocument doc(filePath);
    bool loadOkay = doc.LoadFile();
    // faile to load the xml file.
    if (!loadOkay) {
        printf( "Could not load xml file %s. Error='%s'. Exiting.\n", filePath,doc.ErrorDesc() );
        exit( 1 );
    }
    TiXmlElement* root = doc.RootElement();

    const int buffSize = 20;
    int width = 32;
    char buff[buffSize];

    TiXmlNode*  item = root->FirstChild( VERSION_NAME );
    sprintf(buff, "%s%llu", VERSION_INITIAL, code.getVersion());
    //sprintf(buff, "%s%llu", VERSION_INITIAL, 4);
    TiXmlNode* txnVersion = item->FirstChild(buff);
    cout << setfill(' ') << setw(width) << "Version:";
    if(txnVersion != NULL) {
    	cout << txnVersion ->ToElement()->GetText() << "\n";
    } else {
    	cout << tiXmlNodeUndefined << "\n";
    }


    item = root->FirstChild( TYPEOFMEDIA_NAME );
    memset(buff, 0, sizeof(char)*buffSize);
    sprintf(buff, "%s%llu", TYPEOFMEDIA_INITIAL, code.getTypeOfMedia());
    cout << setfill(' ') << setw(width) << "Type of Media:" << item->FirstChild(buff)->ToElement()->GetText() << "\n";

    item = root->FirstChild( PRIOANDPOLI_NAME );
    memset(buff, 0, sizeof(char)*buffSize);
    sprintf(buff, "%s%llu", PRIOANDPOLI_INITIAL, code.getPrioAndPoli());
    cout << setfill(' ') << setw(width) << "Prio and Poli:" << item->FirstChild(buff)->ToElement()->GetText() << "\n";


    cout << setfill(' ') << setw(width) << "Flag:" << code.getFlag() << "\n";
    cout << setfill(' ') << setw(width) << "Parse Rule:" << code.getParseRule() << "\n";

    item = root->FirstChild( SOUROFCONT_NAME );
    memset(buff, 0, sizeof(char)*buffSize);
    sprintf(buff, "%s%llu", SOUROFCONT_INITIAL, code.getSourOfCont());
    cout << setfill(' ') << setw(width) << "Source of Content:" << item->FirstChild(buff)->ToElement()->GetText() << "\n";

    TiXmlNode* item00 = root->FirstChild( CATEGORY_NAME );
    memset(buff, 0, sizeof(char)*buffSize);
    sprintf(buff, "%s%llu", CATEGORY_INITIAL, code.getCategory());
    //printf("%s, %s\n", CATEGORY_NAME, buff);
    cout << setfill(' ') << setw(width) << "Category:" << item00->FirstChild(buff)->ToElement()->GetText() << "\n";

    cout << setfill(' ') << setw(width) << "Category:" << code.getSubCategory() << "\n";
    cout << setfill(' ') << setw(width) << "Subcategory:" << code.getSubCategory() << "\n";

    item = root->FirstChild( TOPIC_NAME );
    memset(buff, 0, sizeof(char)*buffSize);
    sprintf(buff, "%s%llu", TOPIC_INITIAL, code.getTopic());
    //printf("%s\n", buff);
    cout << setfill(' ') << setw(width) << "Topic:" << item->FirstChild(buff)->ToElement()->GetText() << "\n";

    cout << setfill(' ') << setw(width) << "Copyright and Type of Cont:" << code.getCopyAndTypeOfCont() << "\n";

    item = root->FirstChild( SECUENERLEVECODE_NAME );
    memset(buff, 0, sizeof(char)*buffSize);
    sprintf(buff, "%s%llu", SECUENERLEVECODE_INITIAL, code.getSecuEnerLeveCode());
    cout << setfill(' ') << setw(width) << "Security Energy Level Code:" << item->FirstChild(buff)->ToElement()->GetText() << "\n";

    item = root->FirstChild( LANGUAGE_NAME );
    memset(buff, 0, sizeof(char)*buffSize);
    sprintf(buff, "%s%llu", LANGUAGE_INITIAL, code.getLanguage());
    //printf("%s\n", buff);
    cout << setfill(' ') << setw(width) << "Language:" << item->FirstChild(buff)->ToElement()->GetText() << "\n";

    cout << setfill(' ') << setw(width) << "Size of Content:" << code.getSizeOfContent() << "\n";
    cout << setfill(' ') << setw(width) << "Time Stamp:" << code.getTimeStamp() << "\n";
    cout << setfill(' ') << setw(width) << "Serial Number:" << code.getSerialNumber() << "\n";
    cout << setfill(' ') << setw(width) << "Multiplex Bytes:" << code.getMultiplexBytes() << "\n";
    cout << setfill(' ') << setw(width) << "Code Check:" << code.getCodeCheck() << endl;
}



void showFromXml2(const UCLCode &code) {

// Read information from xml file.
// define xml file path, as follow , we use relative path,
// but you can use absolute path also.
    const char* filePath = "./zc_conf_xml/zcConf.xml";
    const char* tiXmlNodeUndefined = "Undefined";
    TiXmlDocument doc(filePath);
    bool loadOkay = doc.LoadFile();
    // failed to load the xml file.
    if (!loadOkay) {
        printf( "Could not load xml file %s. Error='%s'. Exiting.\n", filePath,doc.ErrorDesc() );
        exit( 1 );
    }
    TiXmlElement* root = doc.RootElement();

    const int buffSize = 20;
    int width = 32;
    char buff[buffSize];

    TiXmlElement* part = root->FirstChildElement(VERSION_NAME);

    TiXmlNode*  item = part->FirstChild( "first" );
    if(item == NULL)  {
    	cout << "333" << endl;
    	return;
    }

    sprintf(buff, "%s%llu", VERSION_INITIAL, code.getVersion());
    //sprintf(buff, "%s%llu", VERSION_INITIAL, 4);
    TiXmlNode* txnVersion = item->FirstChild(buff);
    cout << setfill(' ') << setw(width) << "Version:";
    if(txnVersion != NULL) {
    	cout << txnVersion ->ToElement()->GetText() << "\n";
    } else {
    	cout << tiXmlNodeUndefined << "\n";
    }
}



/**
 * 本模块单元测试程序
 */
void test_code_xml()
{
    UCLCode code_test;

    cout << "new a UCLCode:\n";
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    //code_test.codeDisplay(code_test);
    //cout << '\n';

    code_test.setVersion(1);
    code_test.setTypeOfMedia(0);
    code_test.setPrioAndPoli(1);
    code_test.setFlag(0x5A);
    code_test.setParseRule(0xfff1);//ff1
    code_test.setSourOfCont(0x3000000);//ffffff1
    code_test.setCategory(1);
    code_test.setSubCategory(0x01);//0x01
    code_test.setTopic(0x101);
    code_test.setCopyAndTypeOfCont(0x46);
    code_test.setSecuEnerLeveCode(0x1B);
    code_test.setLanguage(8);
    code_test.setSizeOfContent(31);
    code_test.setTimeStamp(time(NULL));
    /*
     * serinal number and multiplex bytes test cases
     * 0xCff1f3 - 0x8fffff31; 0x8f1f - 0x1f3f5f7f9f; 0x4f - 0x1f3f5f7f9f48; 0xf - 0x1f3f5f7f9f48
     */
    code_test.setSerialNumber(0x4f);
    code_test.setMultiplexBytes(0x1f3f5f7f9f48);


    string s = code_test.pack(); //

    code_test.showCodeHex(s);
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

    code_test.showCode();
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

    cout << "result from xml : " << endl;
    showCodeFromXML(code_test);
    cout << endl;

//    cout << "result from xml : " << endl;
//    showFromXml(code_test);
//    cout << "===========" << endl;


}

void testRead() {
	//const char* filePath = "F:\\eclipseC++\\ZC_V1.1\\zc_conf_xml\\test.xml";
	//const char* filePath = "F:\\eclipseC++\\ZC_V1.1\\code\\test.xml";
    const char* filePath = "./zc_conf_xml/zcConf.xml";
    //readXml(filePath);
    readUCLXml(filePath);
//	const char* filePath = "./zc_conf_xml/test.xml";//鐩稿璺緞鏄浉瀵逛簬Binaries鐩綍涓嬬殑鍙墽琛屾枃浠�
//	readXml(filePath);
//	const char* filePath2 = "./zc_conf_xml/zc_conf.xml";
//	readXml(filePath2);
}


