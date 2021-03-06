/*
 *  Created on: 2016-12-5
 *      Author: Oneway
 *
 *      Modified by Oneway on 2017/6/1.
 *
 *      Add getField and getMBU
 *      Modified by Oneway on 2017/7/30
 */



#ifndef UCL_V0_1_UCLFORMATV2_H
#define UCL_V0_1_UCLFORMATV2_H

#define CODE_BYTES 32 //UCLcode 字节数

/*
 * 按照如下格式定义UCLcode域
 * 域的开始字节（从0开始）
 * 域的开始bit位（从0开始）
 * 域的bit位长度
 * 域的MBU数目
 */

//version格式定义
#define VERSION_START_BYTE 0
#define VERSION_START_BIT 0
#define VERSION_BIT_LENGTH 3
#define VERSION_MBU_NUMS 1

//type of Media
#define TYPEOFMEDIA_START_BYTE 0
#define TYPEOFMEDIA_START_BIT 3
#define TYPEOFMEDIA_BIT_LENGTH 5
#define TYPEOFMEDIA_MBU_NUMS 1

//priority and policy
#define PRIOANDPOLI_START_BYTE 1
#define PRIOANDPOLI_START_BIT 0
#define PRIOANDPOLI_BIT_LENGTH 8
#define PRIOANDPOLI_MBU_NUMS 4

//flag
#define FLAG_START_BYTE 2
#define FLAG_START_BIT 0
#define FLAG_BIT_LENGTH 8
#define FLAG_MBU_NUMS 8

//parse rule
#define PARSERULE_START_BYTE 3
#define PARSERULE_START_BIT 0
#define PARSERULE_BIT_LENGTH 12
#define PARSERULE_MBU_NUMS 2

//source of content
#define SOUROFCONT_START_BYTE 4
#define SOUROFCONT_START_BIT 4
#define SOUROFCONT_BIT_LENGTH 28
#define SOUROFCONT_MBU_NUMS 3

//category
#define CATEGORY_START_BYTE 8
#define CATEGORY_START_BIT 0
#define CATEGORY_BIT_LENGTH 8
#define CATEGORY_MBU_NUMS 1

//subcategory
#define SUBCATEGORY_START_BYTE 9
#define SUBCATEGORY_START_BIT 0
#define SUBCATEGORY_BIT_LENGTH 8
#define SUBCATEGORY_MBU_NUMS 1

//topic
#define TOPIC_START_BYTE 10
#define TOPIC_START_BIT 0
#define TOPIC_BIT_LENGTH 32
#define TOPIC_MBU_NUMS 3

//copyright and type of content
#define COPYANDTYPEOFCONT_START_BYTE 14
#define COPYANDTYPEOFCONT_START_BIT 0
#define COPYANDTYPEOFCONT_BIT_LENGTH 8
#define COPYANDTYPEOFCONT_MBU_NUMS 5

//security energy level code
#define SECUENERLEVECODE_START_BYTE 15
#define SECUENERLEVECODE_START_BIT 0
#define SECUENERLEVECODE_BIT_LENGTH 8
#define SECUENERLEVECODE_MBU_NUMS 3

//language
#define LANGUAGE_START_BYTE 16
#define LANGUAGE_START_BIT 0
#define LANGUAGE_BIT_LENGTH 8
#define LANGUAGE_MBU_NUMS 2

//size of content
#define SIZEOFCONTENT_START_BYTE 17
#define SIZEOFCONTENT_START_BIT 0
#define SIZEOFCONTENT_BIT_LENGTH 5
#define SIZEOFCONTENT_MBU_NUMS 2

//time stamp
#define TIMESTAMP_START_BYTE 17
#define TIMESTAMP_START_BIT 5
#define TIMESTAMP_BIT_LENGTH 43
#define TIMESTAMP_MBU_NUMS 2

//serial number
#define SERIALNUMBER_START_BYTE 23
#define SERIALNUMBER_START_BIT 0
#define SERIALNUMBER_MAX_LENGTH 24
#define SERIALNUMBER_DEFAULT_LENGTH 8
//the length of serial number depends on it's first two bits

//multiplex bytes
//the start byte of multiplex bytes depends on the length of serial number
#define MULTIPLEXBYTES_START_BIT 0
#define MULTIPLEXBYTES_MAX_LENGTH 48
#define MULTIPLEX_END_BYTE 30
//the length of multiplex bytes depends on it's start byte

//code check
#define CODECHECK_START_BYTE 30
#define CODECHECK_START_BIT 0
#define CODECHECK_BIT_LENGTH 16


#endif //UCL_V0_1_UCLFORMATV2_H
