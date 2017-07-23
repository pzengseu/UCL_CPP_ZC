/*
 * xmltest.cpp
 *
 *  Created on: 2017-7-22
 *      Author: Administrator
 */

#include "./header_file/XMLTools.h"
#include <stdio.h>




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

void showFromXml(const UCLCode &code) {

// Read information from xml file.
// define xml file path, as follow , we use relative path,
// but you can use absolute path also.
    const char* filePath = "../zc_conf_xml/zcConf.xml";
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
    sprintf(buff, "%s%lu", VERSION_INITIAL, code.getVersion());
    cout << setfill(' ') << setw(width) << "Version:" << item->FirstChild(buff)->ToElement()->GetText() << "\n";

    item = root->FirstChild( TYPEOFMEDIA_NAME );
    memset(buff, 0, sizeof(char)*buffSize);
    sprintf(buff, "%s%lu", TYPEOFMEDIA_INITIAL, code.getTypeOfMedia());
    cout << setfill(' ') << setw(width) << "Type of Media:" << item->FirstChild(buff)->ToElement()->GetText() << "\n";

    item = root->FirstChild( PRIOANDPOLI_NAME );
    memset(buff, 0, sizeof(char)*buffSize);
    sprintf(buff, "%s%u", PRIOANDPOLI_INITIAL, code.getPrioAndPoli());
    cout << setfill(' ') << setw(width) << "Prio and Poli:" << item->FirstChild(buff)->ToElement()->GetText() << "\n";


    cout << setfill(' ') << setw(width) << "Flag:" << code.getFlag() << "\n";
    cout << setfill(' ') << setw(width) << "Parse Rule:" << code.getParseRule() << "\n";

    item = root->FirstChild( SOUROFCONT_NAME );
    memset(buff, 0, sizeof(char)*buffSize);
    sprintf(buff, "%s%lu", SOUROFCONT_INITIAL, code.getSourOfCont());
    cout << setfill(' ') << setw(width) << "Source of Content:" << item->FirstChild(buff)->ToElement()->GetText() << "\n";

//    TiXmlNode* item00 = root->FirstChild( CATEGORY_NAME );
//    memset(buff, 0, sizeof(char)*buffSize);
//    sprintf(buff, "%s%lu", CATEGORY_INITIAL, code.getCategory());
//    //printf("%s, %s\n", CATEGORY_NAME, buff);
//    cout << setfill(' ') << setw(width) << "Category:" << item00->FirstChild(buff)->ToElement()->GetText() << "\n";

    cout << setfill(' ') << setw(width) << "Category:" << code.getSubCategory() << "\n";
    cout << setfill(' ') << setw(width) << "Subcategory:" << code.getSubCategory() << "\n";

//    item = root->FirstChild( TOPIC_NAME );
//    memset(buff, 0, sizeof(char)*buffSize);
//    sprintf(buff, "%s%lu", TOPIC_INITIAL, code.getTopic());
//    printf("%s\n", buff);
//    cout << setfill(' ') << setw(width) << "Topic:" << item->FirstChild(buff)->ToElement()->GetText() << "\n";

    cout << setfill(' ') << setw(width) << "Topic:" << code.getTopic() << "\n";
    cout << setfill(' ') << setw(width) << "Copyright and Type of Cont:" << code.getCopyAndTypeOfCont() << "\n";

    item = root->FirstChild( SECUENERLEVECODE_NAME );
    memset(buff, 0, sizeof(char)*buffSize);
    sprintf(buff, "%s%lu", SECUENERLEVECODE_INITIAL, code.getSecuEnerLeveCode());
    cout << setfill(' ') << setw(width) << "Security Energy Level Code:" << item->FirstChild(buff)->ToElement()->GetText() << "\n";

//    item = root->FirstChild( LANGUAGE_NAME );
//    memset(buff, 0, sizeof(char)*buffSize);
//    sprintf(buff, "%s%lu", LANGUAGE_INITIAL, code.getLanguage());
//    //printf("%s\n", buff);
//    cout << setfill(' ') << setw(width) << "Language:" << item->FirstChild(buff)->ToElement()->GetText() << "\n";

    cout << setfill(' ') << setw(width) << "Language:" << code.getLanguage() << "\n";
    cout << setfill(' ') << setw(width) << "Size of Content:" << code.getSizeOfContent() << "\n";
    cout << setfill(' ') << setw(width) << "Time Stamp:" << code.getTimeStamp() << "\n";
    cout << setfill(' ') << setw(width) << "Serial Number:" << code.getSerialNumber() << "\n";
    cout << setfill(' ') << setw(width) << "Multiplex Bytes:" << code.getMultiplexBytes() << "\n";
    cout << setfill(' ') << setw(width) << "Code Check:" << code.getCodeCheck() << endl;
}

void test_code_xml()
{
    UCLCode code_test;

    cout << "new a UCLCode:\n";

    code_test.codeDisplay(code_test);
    cout << '\n';

    code_test.setVersion(1);
    code_test.setTypeOfMedia(1);
    code_test.setPrioAndPoli(1);
    code_test.setFlag(13);
    code_test.setParseRule(0xfff1);//ff1有效
    code_test.setSourOfCont(2);//ffffff1有效
    code_test.setCategory(1);
    code_test.setSubCategory(257);//0x01有效
    code_test.setTopic(3);
    code_test.setCopyAndTypeOfCont(254);
    code_test.setSecuEnerLeveCode(3);
    code_test.setLanguage(1);
    code_test.setSizeOfContent(31);
    code_test.setTimeStamp(time(NULL));
    /*
     * serinal number and multiplex bytes test cases
     * 0xCff1f3 - 0x8fffff31; 0x8f1f - 0x1f3f5f7f9f; 0x4f - 0x1f3f5f7f9f48; 0xf - 0x1f3f5f7f9f48
     */
    code_test.setSerialNumber(0x4f);
    code_test.setMultiplexBytes(0x1f3f5f7f9f48);


    string s = code_test.pack(); //打包测试,自动生成校验码

    code_test.showCode();
    cout << '\n';

    showFromXml(code_test);

}

void testRead() {
	//const char* filePath = "F:\\eclipseC++\\ZC_V1.1\\zc_conf_xml\\test.xml";
	//const char* filePath = "F:\\eclipseC++\\ZC_V1.1\\code\\test.xml";
    const char* filePath = "../zc_conf_xml/zcConf.xml";
    //readXml(filePath);
    readUCLXml(filePath);
//	const char* filePath = "./zc_conf_xml/test.xml";//相对路径是相对于Binaries目录下的可执行文件
//	readXml(filePath);
//	const char* filePath2 = "./zc_conf_xml/zc_conf.xml";
//	readXml(filePath2);
}


