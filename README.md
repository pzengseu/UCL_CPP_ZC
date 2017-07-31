# UCL_CPP_ZC
[TOC]
1. 建立UCL对象
```
    UCL ucl；
```

2. 添加UCLCode对象
```
    UCLCode uclCode = UCLCode code_test = generateCode();
    ucl.setUclCode(code_test);
```
generateCode方法如下:
```
 UCLCode generateCode() {
     UCLCode code_test;
 
     code_test.setVersion(1);
     code_test.setTypeOfMedia(9);
     code_test.setPrioAndPoli(15);
     code_test.setFlag(0x4E); //01001110
     code_test.setParseRule(0xfff1);//ff1有效
     code_test.setSourOfCont(0xfffffff1);//ffffff1有效
     code_test.setCategory(255);
     code_test.setSubCategory(257);//0x01有效
     code_test.setTopic(0xffffff1);
     code_test.setCopyAndTypeOfCont(254);
     code_test.setSecuEnerLeveCode(251);
     code_test.setLanguage(253);
     code_test.setSizeOfContent(31);
     code_test.setTimeStamp(0x3fffffffff9f9);
     /*
      * serinal number and multiplex bytes test cases
      * 0xCff1f3 - 0x8fffff31; 0x8f1f - 0x1f3f5f7f9f; 0x4f - 0x1f3f5f7f9f48; 0xf - 0x1f3f5f7f9f48
      */
     code_test.setSerialNumber(0x4f);
     code_test.setMultiplexBytes(0x1f3f5f7f9f48);
 
     code_test.setVersion(3);//对于已经设置过的域重复设置
 
     return code_test;
 }
```
主要是使用UCLCode中的setXXX方法设置UCLCode中各个域的值（code check会根据需要自动生成）。

3. 创建固有属性集合-CDPS
```
    UCLPropertySet cdps = generateCDPS();
    ucl.setPropertySet(cdps);
```
generateCDPS()方法如下：
```
UCLPropertySet generateCDPS()
{
    UCLPropertySet cdps;
    cdps.setHeadCategory(1);
    UCLPropertyBase title = GenCDPSProperty::genTitle("江苏今年起实施“12311”计划 培育百个农业特色镇");
    UCLPropertyBase file = GenCDPSProperty::genFileDescription("文本;10M");
    UCLPropertyBase content = GenCDPSProperty::genContObject("江苏今年起实施“12311”计划, 全省创意休闲农业工作推进会");
    cdps.setProperty(title);
    cdps.setProperty(file);
    cdps.setProperty(content);

    return cdps;
}
```
- 首先新建集合对象;
- 然后调用setHeadCategory方法设置集合类别;
- 创建固有属性或自定义属性;
- 将属性添加到属性集合中。
- 将属性集合添加到UCL中。

4. 创建固有属性集合-CGPS
```
    UCLPropertySet cgps = generateCGPS();
    ucl.setPropertySet(cgps);
```
generateCGPS()方法如下:
```
    UCLPropertySet generateCGPS()
    {
        UCLPropertySet cgps;
        cgps.setHeadCategory(15);
        UCLPropertyBase sigCon = GenCGPSProperty::genContSig("江苏今年起实施“12311”计划, 全省创意休闲农业工作推进会", SHA_512, ECDSA);
        cgps.setProperty(sigCon);
        UCLPropertyBase sigUCL = GenCGPSProperty::genUCLSig(MD5, RSA);
        cgps.setProperty(sigUCL);
    
        return cgps;
    }
```

5. UCL中增加关联UCL
```
string rstr = "";

UCLCode rCode = code_test;
rCode.setFlag(0);
rstr += rCode.pack();

UCL rUCL = generateRUCL();
rstr += rUCL.pack();

UCLPropertyBase related = GenCDPSProperty::genRelatedUCL(2, rstr);
ucl.setProperty(1, related);
```

6. 打包解包
```
ucl.pack()  //自动生成摘要字段,并返回打包的string流

UCL ucl2;
ucl2.unpack(ucl.pack());  
```
- 自动生成摘要字段, 打包ucl对象成string对象；
- 将string对象解包成ucl对象, 从而可以获取每个字段值。

7. 战场目标中UCL标准常用属性
结合战场目标实际情况，标准UCL属性部分主要用到以下属性：
###### CDPS：
- 标题
- 文件信息
- 关联UCL
- 内容对象

###### CGPS：
- 内容数字签名
- UCL数字签名

8. 战场目标属性集合
- 目标对象名称（属性元素类别号为1）； 
- 空间位置信息（属性元素类别号为2）； 
- 时间信息（属性元素类别号为3）； 
- 目标外形（属性元素类别号为4）； 
- 物理特性（属性元素类别号为5）； 
- 目标材质（属性元素类别号为6）； 
- 通过程度（属性元素类别号为7）；
- 空间状况信息（属性元素类别号为8）； 
- 绝对运动特性（属性元素类别号为11）；
- 相对运动特性（属性元素类别号为12）；
- 运行轨迹（属性元素类别号为13）。

9. 添加ZCPS属性集合
```
    UCLPropertySet zcps = generateZCPS();
    ucl.setPropertySet(zcps);
```
generateZCPS()方法如下：
```
UCLPropertySet generateZCPS()
{
    UCLPropertySet zcps;
    zcps.setHeadCategory(2);

    UCLPropertyBase name = GenZCPSProperty::genName("战场");
    zcps.setProperty(name);

    UCLPropertyBase spaceLoc = GenZCPSProperty::genSpaceLoc("北纬N39°40′20.09″ 东经E116°32′13.51");
    zcps.setProperty(spaceLoc);

    time_t timer = time(NULL);
    struct tm * tblock;
    tblock = localtime(&timer);
    UCLPropertyBase time = GenZCPSProperty::genTime(asctime(tblock));
    zcps.setProperty(time);

    UCLPropertyBase shape = GenZCPSProperty::genShape("1;北纬N39°40′20.09″ 东经E116°32′13.51");
    zcps.setProperty(shape);

    UCLPropertyBase phy = GenZCPSProperty::genPhysical("0;;1;");
    zcps.setProperty(phy);

    UCLPropertyBase material = GenZCPSProperty::genMaterial("1");
    zcps.setProperty(material);

    UCLPropertyBase pass = GenZCPSProperty::genPassingAbility("1");
    zcps.setProperty(pass);

    UCLPropertyBase spaceEnemyS = GenZCPSProperty::genSpaceEnemyS("坦克;;潜艇");
    zcps.setProperty(spaceEnemyS);

    UCLPropertyBase amf = GenZCPSProperty::genAbsMotionFea("10;;北纬N39°40′20.09″ 东经E116°32′13.51");
    zcps.setProperty(amf);

    UCLPropertyBase rmf = GenZCPSProperty::genRelMotionFea("10;100;北纬N39°40′20.09″ 东经E116°32′13.51");
    zcps.setProperty(rmf);

    UCLPropertyBase tp = GenZCPSProperty::genTravellingPath("10;;北纬N39°40′20.09″ 东经E116°32′13.51");
    zcps.setProperty(tp);

    return zcps;
}
```

#### UCL控制台例子testCommand(), 输出如下。
```
/home/zp/UCL_CPP_ZC/cmake-build-debug/UCL_CPP_ZC

========== UCL test begin==========

##############测试属性##############

--------------UCLPackage-------------- 
69-0f-4e-ff-1f-ff-ff-f1-ff-01-0f-ff-ff-f1-fe-fb-fd-3f-ff-ff-ff-f9-f9-4f-1f-3f-5f-7f-9f-48-12-a9-01-48-e5-03-06-80-01-4c-84-01-02-c2-01-00-45-e6-b1-9f-e8-8b-8f-e4-bb-8a-e5-b9-b4-e8-b5-b7-e5-ae-9e-e6-96-bd-e2-80-9c-31-32-33-31-31-e2-80-9d-e8-ae-a1-e5-88-92-20-e5-9f-b9-e8-82-b2-e7-99-be-e4-b8-aa-e5-86-9c-e4-b8-9a-e7-89-b9-e8-89-b2-e9-95-87-09-00-0d-e6-96-87-e6-9c-ac-3b-31-30-4d-0e-08-da-69-0f-00-ff-1f-ff-ff-f1-ff-01-0f-ff-ff-f1-fe-fb-fd-17-ff-ff-ff-f9-f9-4f-1f-3f-5f-7f-9f-48-3a-6f-69-0f-40-ff-1f-ff-ff-f1-ff-01-0f-ff-ff-f1-fe-fb-fd-27-ff-ff-ff-f9-f9-4f-1f-3f-5f-7f-9f-48-4a-90-01-04-97-02-80-01-00-4a-02-00-01-00-45-e6-b1-9f-e8-8b-8f-e4-bb-8a-e5-b9-b4-e8-b5-b7-e5-ae-9e-e6-96-bd-e2-80-9c-31-32-33-31-31-e2-80-9d-e8-ae-a1-e5-88-92-20-e5-9f-b9-e8-82-b2-e7-99-be-e4-b8-aa-e5-86-9c-e4-b8-9a-e7-89-b9-e8-89-b2-e9-95-87-0f-00-48-00-80-3f-0c-43-4d-43-77-43-46-42-57-6f-4b-4d-30-5a-4e-44-69-32-6f-2f-42-2f-4c-39-54-57-32-65-79-39-68-63-63-61-41-68-51-56-48-4d-57-44-6e-36-63-58-33-48-78-43-65-4c-63-70-41-56-41-6d-69-71-6a-72-57-67-3d-3d-0f-00-52-e6-b1-9f-e8-8b-8f-e4-bb-8a-e5-b9-b4-e8-b5-b7-e5-ae-9e-e6-96-bd-e2-80-9c-31-32-33-31-31-e2-80-9d-e8-ae-a1-e5-88-92-2c-20-e5-85-a8-e7-9c-81-e5-88-9b-e6-84-8f-e4-bc-91-e9-97-b2-e5-86-9c-e4-b8-9a-e5-b7-a5-e4-bd-9c-e6-8e-a8-e8-bf-9b-e4-bc-9a-02-68-57-01-fe-39-01-00-09-e6-88-98-e5-9c-ba-02-08-32-e5-8c-97-e7-ba-ac-4e-33-39-c2-b0-34-30-e2-80-b2-32-30-2e-30-39-e2-80-b3-20-e4-b8-9c-e7-bb-8f-45-31-31-36-c2-b0-33-32-e2-80-b2-31-33-2e-35-31-03-08-1c-53-75-6e-20-4a-75-6c-20-33-30-20-32-32-3a-34-31-3a-33-32-20-32-30-31-37-0a-04-00-34-31-3b-e5-8c-97-e7-ba-ac-4e-33-39-c2-b0-34-30-e2-80-b2-32-30-2e-30-39-e2-80-b3-20-e4-b8-9c-e7-bb-8f-45-31-31-36-c2-b0-33-32-e2-80-b2-31-33-2e-35-31-05-00-08-30-3b-3b-31-3b-06-00-04-31-07-00-04-31-08-00-11-e5-9d-a6-e5-85-8b-3b-3b-e6-bd-9c-e8-89-87-0b-04-36-31-30-3b-3b-e5-8c-97-e7-ba-ac-4e-33-39-c2-b0-34-30-e2-80-b2-32-30-2e-30-39-e2-80-b3-20-e4-b8-9c-e7-bb-8f-45-31-31-36-c2-b0-33-32-e2-80-b2-31-33-2e-35-31-0c-04-39-31-30-3b-31-30-30-3b-e5-8c-97-e7-ba-ac-4e-33-39-c2-b0-34-30-e2-80-b2-32-30-2e-30-39-e2-80-b3-20-e4-b8-9c-e7-bb-8f-45-31-31-36-c2-b0-33-32-e2-80-b2-31-33-2e-35-31-0d-08-36-31-30-3b-3b-e5-8c-97-e7-ba-ac-4e-33-39-c2-b0-34-30-e2-80-b2-32-30-2e-30-39-e2-80-b3-20-e4-b8-9c-e7-bb-8f-45-31-31-36-c2-b0-33-32-e2-80-b2-31-33-2e-35-31-0f-44-04-01-00-90-2c-10-4f-4d-44-55-43-47-44-69-55-69-45-77-46-50-59-38-66-65-54-56-77-69-4c-75-44-4f-53-2b-44-73-65-33-56-43-70-79-72-44-67-49-5a-41-4b-7a-45-46-31-6e-56-31-45-70-76-57-71-37-35-61-77-2f-6b-6d-72-6d-46-39-34-73-63-30-45-42-6a-65-67-3d-3d-1f-08-af-4e-32-36-54-56-66-51-74-44-5a-79-56-79-74-31-78-48-74-49-59-41-49-79-6c-78-45-6c-67-46-7a-44-6e-75-35-35-6d-30-61-78-4f-73-6b-4d-33-33-69-32-54-6a-44-48-6a-61-6e-52-35-42-2b-46-46-36-31-4d-47-64-4c-74-58-31-39-62-46-64-59-74-67-5a-2f-49-37-54-4b-42-42-71-4b-4b-41-6f-63-48-52-6b-62-4b-48-4f-4b-4a-52-34-4d-72-6b-7a-68-41-6a-43-43-67-78-2f-63-79-72-2b-4a-4a-50-2b-30-59-51-71-59-79-55-42-43-63-71-72-76-79-4e-45-6b-63-77-7a-54-4c-48-4c-65-52-2b-71-33-4a-31-75-30-72-62-54-7a-35-55-6e-67-6a-76-37-63-32-64-47-4c-41-3d-

--------------显示UCL各部分关键信息--------------
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                         VERSION : Version-3
                     TYPEOFMEDIA : Search Engine
                     PRIOANDPOLI : Priority : 0
                     PRIOANDPOLI : Non-preemptive Mode
                     PRIOANDPOLI : Timing Issue
                     PRIOANDPOLI : Circularly Issue In 48 Hour
                            FLAG : Code Part Does Not Extend
                            FLAG : Have Properties Part
                            FLAG : Multiplex Bytes Do Not Have Timing Or Circularly Issue Information
                            FLAG : Multiplex Bytes Do Not Have Information Defined By Application
                            FLAG : UCL Package Is Integrated
                            FLAG : Have Related UCLs
                            FLAG : Have User-defined Property Set
                            FLAG : 1(B)
                       PARSERULE : 000002(B)
                       PARSERULE : 000002(B)
                      SOUROFCONT : 001(B)
                      SOUROFCONT : 1(B)
                      SOUROFCONT : 000000000000000000000001(B)
                        CATEGORY : 00000003(B)
                     SUBCATEGORY : Squad
                           TOPIC : Common Topic
                           TOPIC : 01(B)
                           TOPIC : 0000000000000000000000000009(B)
               COPYANDTYPEOFCONT : Have Copyright Information
               COPYANDTYPEOFCONT : Direct Command
               COPYANDTYPEOFCONT : Free Content
               COPYANDTYPEOFCONT : 1(B)
               COPYANDTYPEOFCONT : 0002(B)
                SECUENERLEVECODE : 01(B)
                SECUENERLEVECODE : Physics Safety Level : 7
                SECUENERLEVECODE : Logic Safety Level : 3
                        LANGUAGE : Other Language
                        LANGUAGE : Property Part Has The Same Language With Meta Language
                   SIZEOFCONTENT : [4, 16)
                   SIZEOFCONTENT : GB
                       TIMESTAMP : 7fffffff9f9	                            TIME : 44883-2-4 c:18:19
                    SERIALNUMBER : 4f
                  MULTIPLEXBYTES : 1f3f5f7f9f48
                       CODECHECK : 12a9
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
--------------属性部分----------------
元语言类型: 中文
属性集个数: 3
--------------具体属性集----------------
**************************
属性集合名: 内容描述属性集合
属性集类别: 1    属性个数: 4
属性类别: 1    属性名: 内容标题
属性值: 江苏今年起实施“12311”计划 培育百个农业特色镇
------------------------------------
属性类别: 9    属性名: 文件信息
文件信息: 文本 10M 
------------------------------------
属性类别: 14    属性名: 关联UCL
关联UCL数量: 2
--------------------------关联UCL开始-----------------------------
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                         VERSION : Version-3
                     TYPEOFMEDIA : Search Engine
                     PRIOANDPOLI : Priority : 0
                     PRIOANDPOLI : Non-preemptive Mode
                     PRIOANDPOLI : Timing Issue
                     PRIOANDPOLI : Circularly Issue In 48 Hour
                            FLAG : Code Part Does Not Extend
                            FLAG : Do Not Have Property Part
                            FLAG : Multiplex Bytes Do Not Have Timing Or Circularly Issue Information
                            FLAG : Multiplex Bytes Do Not Have Information Defined By Application
                            FLAG : UCL Package And Content Object Is detached
                            FLAG : Do Not Have Related UCLs
                            FLAG : Do Not Have User-defined Property Set
                            FLAG : 1(B)
                       PARSERULE : 000002(B)
                       PARSERULE : 000002(B)
                      SOUROFCONT : 001(B)
                      SOUROFCONT : 1(B)
                      SOUROFCONT : 000000000000000000000001(B)
                        CATEGORY : 00000003(B)
                     SUBCATEGORY : Squad
                           TOPIC : Common Topic
                           TOPIC : 01(B)
                           TOPIC : 0000000000000000000000000009(B)
               COPYANDTYPEOFCONT : Have Copyright Information
               COPYANDTYPEOFCONT : Direct Command
               COPYANDTYPEOFCONT : Free Content
               COPYANDTYPEOFCONT : 1(B)
               COPYANDTYPEOFCONT : 0002(B)
                SECUENERLEVECODE : 01(B)
                SECUENERLEVECODE : Physics Safety Level : 7
                SECUENERLEVECODE : Logic Safety Level : 3
                        LANGUAGE : Other Language
                        LANGUAGE : Property Part Has The Same Language With Meta Language
                   SIZEOFCONTENT : [1, 4)
                   SIZEOFCONTENT : MB
                       TIMESTAMP : 8796093020665	                            TIME : 280707-2-4 12:24:25
                    SERIALNUMBER : 79
                  MULTIPLEXBYTES : 34357045600072
                       CODECHECK : 14959
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                         VERSION : Version-3
                     TYPEOFMEDIA : Search Engine
                     PRIOANDPOLI : Priority : 0
                     PRIOANDPOLI : Non-preemptive Mode
                     PRIOANDPOLI : Timing Issue
                     PRIOANDPOLI : Circularly Issue In 48 Hour
                            FLAG : Code Part Does Not Extend
                            FLAG : Have Properties Part
                            FLAG : Multiplex Bytes Do Not Have Timing Or Circularly Issue Information
                            FLAG : Multiplex Bytes Do Not Have Information Defined By Application
                            FLAG : UCL Package And Content Object Is detached
                            FLAG : Do Not Have Related UCLs
                            FLAG : Do Not Have User-defined Property Set
                            FLAG : 1(B)
                       PARSERULE : 000002(B)
                       PARSERULE : 000002(B)
                      SOUROFCONT : 001(B)
                      SOUROFCONT : 1(B)
                      SOUROFCONT : 000000000000000000000001(B)
                        CATEGORY : 00000003(B)
                     SUBCATEGORY : Squad
                           TOPIC : Common Topic
                           TOPIC : 01(B)
                           TOPIC : 0000000000000000000000000009(B)
               COPYANDTYPEOFCONT : Have Copyright Information
               COPYANDTYPEOFCONT : Direct Command
               COPYANDTYPEOFCONT : Free Content
               COPYANDTYPEOFCONT : 1(B)
               COPYANDTYPEOFCONT : 0002(B)
                SECUENERLEVECODE : 01(B)
                SECUENERLEVECODE : Physics Safety Level : 7
                SECUENERLEVECODE : Logic Safety Level : 3
                        LANGUAGE : Other Language
                        LANGUAGE : Property Part Has The Same Language With Meta Language
                   SIZEOFCONTENT : [4, 16)
                   SIZEOFCONTENT : B
                       TIMESTAMP : 8796093020665	                            TIME : 280707-2-4 12:24:25
                    SERIALNUMBER : 79
                  MULTIPLEXBYTES : 34357045600072
                       CODECHECK : 19088
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
--------------属性部分----------------
元语言类型: 中文
属性集个数: 2
--------------具体属性集----------------
**************************
属性集合名: 内容描述属性集合
属性集类别: 1    属性个数: 1
属性类别: 1    属性名: 内容标题
属性值: 江苏今年起实施“12311”计划 培育百个农业特色镇
------------------------------------
**************************
属性集合名: 内容管理属性集合
属性集类别: 15    属性个数: 1
属性类别: 15    属性名: 全UCL包数字签名
数字摘要算法: SHA-256   数字签名算法: DSA
摘要或签名信息: MCwCFBWoKM0ZNDi2o/B/L9TW2ey9hccaAhQVHMWDn6cX3HxCeLcpAVAmiqjrWg==
------------------------------------
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
--------------------------关联UCL结束-----------------------------
------------------------------------
属性类别: 15    属性名: 内容对象
属性值: 江苏今年起实施“12311”计划, 全省创意休闲农业工作推进会
------------------------------------
**************************
属性集合名: ZC目标对象编码体系属性集合
属性集类别: 2    属性个数: 11
属性类别: 1    属性名: 目标对象名称
名称: 战场
------------------------------------
属性类别: 2    属性名: 空间位置信息
坐标体系描述位置标准：GPS
位置坐标：北纬N39°40′20.09″ 东经E116°32′13.51
------------------------------------
属性类别: 3    属性名: 时间信息
授时信息规则：GPS
时间：Sun Jul 30 22:41:32 2017
------------------------------------
属性类别: 4    属性名: 目标外形
几何轮廓: 1, 长方形
投影边界: 北纬N39°40′20.09″ 东经E116°32′13.51
------------------------------------
属性类别: 5    属性名: 物理特性
电磁特性: 0, 反射电磁波
声波特性: , 反射声波
核生化特性: 1, 不产生核辐射
雷达特性: , 可被雷达检测
------------------------------------
属性类别: 6    属性名: 目标材质
材质: 1, 塑料材质
------------------------------------
属性类别: 7    属性名: 通过程度
通过程度: 1, 可通过
------------------------------------
属性类别: 8    属性名: 空间状况信息地
地面敌我状态信息: 坦克
空中敌我环境信息: 
水下敌我状况信息: 潜艇
------------------------------------
属性类别: 11    属性名: 绝对运动特性
运动特性解析信息: 速度单位为厘米每秒（cm/s），加速度单位为厘米每秒平方（cm/s2）
速度: 10
加速度: 
运动轨迹: 北纬N39°40′20.09″ 东经E116°32′13.51
------------------------------------
属性类别: 12    属性名: 相对运动特性
运动特性解析信息: 速度单位为厘米每秒（cm/s），加速度单位为厘米每秒平方（cm/s2）
速度: 10
加速度: 100
运动轨迹: 北纬N39°40′20.09″ 东经E116°32′13.51
------------------------------------
属性类别: 13    属性名: 运行轨迹
运动轨迹解析信息: GPS
运动轨迹: 10;;北纬N39°40′20.09″ 东经E116°32′13.51
------------------------------------
**************************
属性集合名: 内容管理属性集合
属性集类别: 15    属性个数: 2
属性类别: 12    属性名: 内容数字签名
数字摘要算法: SHA-512   数字签名算法: ECDSA
摘要或签名信息: MDUCGDiUiEwFPY8feTVwiLuDOS+Dse3VCpyrDgIZAKzEF1nV1EpvWq75aw/kmrmF94sc0EBjeg==
------------------------------------
属性类别: 15    属性名: 全UCL包数字签名
数字摘要算法: MD5   数字签名算法: RSA
摘要或签名信息: N26TVfQtDZyVyt1xHtIYAIylxElgFzDnu55m0axOskM33i2TjDHjanR5B+FF61MGdLtX19bFdYtgZ/I7TKBBqKKAocHRkbKHOKJR4MrkzhAjCCgx/cyr+JJP+0YQqYyUBCcqrvyNEkcwzTLHLeR+q3J1u0rbTz5Ungjv7c2dGLA=
------------------------------------

##############测试解包##############

--------------UCLPackage--------------
69-0f-4e-ff-1f-ff-ff-f1-ff-01-0f-ff-ff-f1-fe-fb-fd-3f-ff-ff-ff-f9-f9-4f-1f-3f-5f-7f-9f-48-12-a9-01-48-e5-03-06-80-01-4c-84-01-02-c2-01-00-45-e6-b1-9f-e8-8b-8f-e4-bb-8a-e5-b9-b4-e8-b5-b7-e5-ae-9e-e6-96-bd-e2-80-9c-31-32-33-31-31-e2-80-9d-e8-ae-a1-e5-88-92-20-e5-9f-b9-e8-82-b2-e7-99-be-e4-b8-aa-e5-86-9c-e4-b8-9a-e7-89-b9-e8-89-b2-e9-95-87-09-00-0d-e6-96-87-e6-9c-ac-3b-31-30-4d-0e-08-da-69-0f-00-ff-1f-ff-ff-f1-ff-01-0f-ff-ff-f1-fe-fb-fd-17-ff-ff-ff-f9-f9-4f-1f-3f-5f-7f-9f-48-3a-6f-69-0f-40-ff-1f-ff-ff-f1-ff-01-0f-ff-ff-f1-fe-fb-fd-27-ff-ff-ff-f9-f9-4f-1f-3f-5f-7f-9f-48-4a-90-01-04-97-02-80-01-00-4a-02-00-01-00-45-e6-b1-9f-e8-8b-8f-e4-bb-8a-e5-b9-b4-e8-b5-b7-e5-ae-9e-e6-96-bd-e2-80-9c-31-32-33-31-31-e2-80-9d-e8-ae-a1-e5-88-92-20-e5-9f-b9-e8-82-b2-e7-99-be-e4-b8-aa-e5-86-9c-e4-b8-9a-e7-89-b9-e8-89-b2-e9-95-87-0f-00-48-00-80-3f-0c-43-4d-43-77-43-46-42-57-6f-4b-4d-30-5a-4e-44-69-32-6f-2f-42-2f-4c-39-54-57-32-65-79-39-68-63-63-61-41-68-51-56-48-4d-57-44-6e-36-63-58-33-48-78-43-65-4c-63-70-41-56-41-6d-69-71-6a-72-57-67-3d-3d-0f-00-52-e6-b1-9f-e8-8b-8f-e4-bb-8a-e5-b9-b4-e8-b5-b7-e5-ae-9e-e6-96-bd-e2-80-9c-31-32-33-31-31-e2-80-9d-e8-ae-a1-e5-88-92-2c-20-e5-85-a8-e7-9c-81-e5-88-9b-e6-84-8f-e4-bc-91-e9-97-b2-e5-86-9c-e4-b8-9a-e5-b7-a5-e4-bd-9c-e6-8e-a8-e8-bf-9b-e4-bc-9a-02-68-57-01-fe-39-01-00-09-e6-88-98-e5-9c-ba-02-08-32-e5-8c-97-e7-ba-ac-4e-33-39-c2-b0-34-30-e2-80-b2-32-30-2e-30-39-e2-80-b3-20-e4-b8-9c-e7-bb-8f-45-31-31-36-c2-b0-33-32-e2-80-b2-31-33-2e-35-31-03-08-1c-53-75-6e-20-4a-75-6c-20-33-30-20-32-32-3a-34-31-3a-33-32-20-32-30-31-37-0a-04-00-34-31-3b-e5-8c-97-e7-ba-ac-4e-33-39-c2-b0-34-30-e2-80-b2-32-30-2e-30-39-e2-80-b3-20-e4-b8-9c-e7-bb-8f-45-31-31-36-c2-b0-33-32-e2-80-b2-31-33-2e-35-31-05-00-08-30-3b-3b-31-3b-06-00-04-31-07-00-04-31-08-00-11-e5-9d-a6-e5-85-8b-3b-3b-e6-bd-9c-e8-89-87-0b-04-36-31-30-3b-3b-e5-8c-97-e7-ba-ac-4e-33-39-c2-b0-34-30-e2-80-b2-32-30-2e-30-39-e2-80-b3-20-e4-b8-9c-e7-bb-8f-45-31-31-36-c2-b0-33-32-e2-80-b2-31-33-2e-35-31-0c-04-39-31-30-3b-31-30-30-3b-e5-8c-97-e7-ba-ac-4e-33-39-c2-b0-34-30-e2-80-b2-32-30-2e-30-39-e2-80-b3-20-e4-b8-9c-e7-bb-8f-45-31-31-36-c2-b0-33-32-e2-80-b2-31-33-2e-35-31-0d-08-36-31-30-3b-3b-e5-8c-97-e7-ba-ac-4e-33-39-c2-b0-34-30-e2-80-b2-32-30-2e-30-39-e2-80-b3-20-e4-b8-9c-e7-bb-8f-45-31-31-36-c2-b0-33-32-e2-80-b2-31-33-2e-35-31-0f-44-04-01-00-90-2c-10-4f-4d-44-55-43-47-44-69-55-69-45-77-46-50-59-38-66-65-54-56-77-69-4c-75-44-4f-53-2b-44-73-65-33-56-43-70-79-72-44-67-49-5a-41-4b-7a-45-46-31-6e-56-31-45-70-76-57-71-37-35-61-77-2f-6b-6d-72-6d-46-39-34-73-63-30-45-42-6a-65-67-3d-3d-1f-08-af-4e-32-36-54-56-66-51-74-44-5a-79-56-79-74-31-78-48-74-49-59-41-49-79-6c-78-45-6c-67-46-7a-44-6e-75-35-35-6d-30-61-78-4f-73-6b-4d-33-33-69-32-54-6a-44-48-6a-61-6e-52-35-42-2b-46-46-36-31-4d-47-64-4c-74-58-31-39-62-46-64-59-74-67-5a-2f-49-37-54-4b-42-42-71-4b-4b-41-6f-63-48-52-6b-62-4b-48-4f-4b-4a-52-34-4d-72-6b-7a-68-41-6a-43-43-67-78-2f-63-79-72-2b-4a-4a-50-2b-30-59-51-71-59-79-55-42-43-63-71-72-76-79-4e-45-6b-63-77-7a-54-4c-48-4c-65-52-2b-71-33-4a-31-75-30-72-62-54-7a-35-55-6e-67-6a-76-37-63-32-64-47-4c-41-3d-

--------------解包后UCL各部分关键信息--------------
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                         VERSION : Version-3
                     TYPEOFMEDIA : Search Engine
                     PRIOANDPOLI : Priority : 0
                     PRIOANDPOLI : Non-preemptive Mode
                     PRIOANDPOLI : Timing Issue
                     PRIOANDPOLI : Circularly Issue In 48 Hour
                            FLAG : Code Part Does Not Extend
                            FLAG : Have Properties Part
                            FLAG : Multiplex Bytes Do Not Have Timing Or Circularly Issue Information
                            FLAG : Multiplex Bytes Do Not Have Information Defined By Application
                            FLAG : UCL Package Is Integrated
                            FLAG : Have Related UCLs
                            FLAG : Have User-defined Property Set
                            FLAG : 1(B)
                       PARSERULE : 000002(B)
                       PARSERULE : 000002(B)
                      SOUROFCONT : 001(B)
                      SOUROFCONT : 1(B)
                      SOUROFCONT : 000000000000000000000001(B)
                        CATEGORY : 00000003(B)
                     SUBCATEGORY : Squad
                           TOPIC : Common Topic
                           TOPIC : 01(B)
                           TOPIC : 0000000000000000000000000009(B)
               COPYANDTYPEOFCONT : Have Copyright Information
               COPYANDTYPEOFCONT : Direct Command
               COPYANDTYPEOFCONT : Free Content
               COPYANDTYPEOFCONT : 1(B)
               COPYANDTYPEOFCONT : 0002(B)
                SECUENERLEVECODE : 01(B)
                SECUENERLEVECODE : Physics Safety Level : 7
                SECUENERLEVECODE : Logic Safety Level : 3
                        LANGUAGE : Other Language
                        LANGUAGE : Property Part Has The Same Language With Meta Language
                   SIZEOFCONTENT : [4, 16)
                   SIZEOFCONTENT : GB
                       TIMESTAMP : 7fffffff9f9	                            TIME : 44883-2-4 c:18:19
                    SERIALNUMBER : 4f
                  MULTIPLEXBYTES : 1f3f5f7f9f48
                       CODECHECK : 12a9
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
--------------属性部分----------------
元语言类型: 中文
属性集个数: 3
--------------具体属性集----------------
**************************
属性集合名: 内容描述属性集合
属性集类别: 1    属性个数: 4
属性类别: 1    属性名: 内容标题
属性值: 江苏今年起实施“12311”计划 培育百个农业特色镇
------------------------------------
属性类别: 9    属性名: 文件信息
文件信息: 文本 10M 
------------------------------------
属性类别: 14    属性名: 关联UCL
关联UCL数量: 2
--------------------------关联UCL开始-----------------------------
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                         VERSION : Version-3
                     TYPEOFMEDIA : Search Engine
                     PRIOANDPOLI : Priority : 0
                     PRIOANDPOLI : Non-preemptive Mode
                     PRIOANDPOLI : Timing Issue
                     PRIOANDPOLI : Circularly Issue In 48 Hour
                            FLAG : Code Part Does Not Extend
                            FLAG : Do Not Have Property Part
                            FLAG : Multiplex Bytes Do Not Have Timing Or Circularly Issue Information
                            FLAG : Multiplex Bytes Do Not Have Information Defined By Application
                            FLAG : UCL Package And Content Object Is detached
                            FLAG : Do Not Have Related UCLs
                            FLAG : Do Not Have User-defined Property Set
                            FLAG : 1(B)
                       PARSERULE : 000002(B)
                       PARSERULE : 000002(B)
                      SOUROFCONT : 001(B)
                      SOUROFCONT : 1(B)
                      SOUROFCONT : 000000000000000000000001(B)
                        CATEGORY : 00000003(B)
                     SUBCATEGORY : Squad
                           TOPIC : Common Topic
                           TOPIC : 01(B)
                           TOPIC : 0000000000000000000000000009(B)
               COPYANDTYPEOFCONT : Have Copyright Information
               COPYANDTYPEOFCONT : Direct Command
               COPYANDTYPEOFCONT : Free Content
               COPYANDTYPEOFCONT : 1(B)
               COPYANDTYPEOFCONT : 0002(B)
                SECUENERLEVECODE : 01(B)
                SECUENERLEVECODE : Physics Safety Level : 7
                SECUENERLEVECODE : Logic Safety Level : 3
                        LANGUAGE : Other Language
                        LANGUAGE : Property Part Has The Same Language With Meta Language
                   SIZEOFCONTENT : [1, 4)
                   SIZEOFCONTENT : MB
                       TIMESTAMP : 8796093020665	                            TIME : 280707-2-4 12:24:25
                    SERIALNUMBER : 79
                  MULTIPLEXBYTES : 34357045600072
                       CODECHECK : 14959
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                         VERSION : Version-3
                     TYPEOFMEDIA : Search Engine
                     PRIOANDPOLI : Priority : 0
                     PRIOANDPOLI : Non-preemptive Mode
                     PRIOANDPOLI : Timing Issue
                     PRIOANDPOLI : Circularly Issue In 48 Hour
                            FLAG : Code Part Does Not Extend
                            FLAG : Have Properties Part
                            FLAG : Multiplex Bytes Do Not Have Timing Or Circularly Issue Information
                            FLAG : Multiplex Bytes Do Not Have Information Defined By Application
                            FLAG : UCL Package And Content Object Is detached
                            FLAG : Do Not Have Related UCLs
                            FLAG : Do Not Have User-defined Property Set
                            FLAG : 1(B)
                       PARSERULE : 000002(B)
                       PARSERULE : 000002(B)
                      SOUROFCONT : 001(B)
                      SOUROFCONT : 1(B)
                      SOUROFCONT : 000000000000000000000001(B)
                        CATEGORY : 00000003(B)
                     SUBCATEGORY : Squad
                           TOPIC : Common Topic
                           TOPIC : 01(B)
                           TOPIC : 0000000000000000000000000009(B)
               COPYANDTYPEOFCONT : Have Copyright Information
               COPYANDTYPEOFCONT : Direct Command
               COPYANDTYPEOFCONT : Free Content
               COPYANDTYPEOFCONT : 1(B)
               COPYANDTYPEOFCONT : 0002(B)
                SECUENERLEVECODE : 01(B)
                SECUENERLEVECODE : Physics Safety Level : 7
                SECUENERLEVECODE : Logic Safety Level : 3
                        LANGUAGE : Other Language
                        LANGUAGE : Property Part Has The Same Language With Meta Language
                   SIZEOFCONTENT : [4, 16)
                   SIZEOFCONTENT : B
                       TIMESTAMP : 8796093020665	                            TIME : 280707-2-4 12:24:25
                    SERIALNUMBER : 79
                  MULTIPLEXBYTES : 34357045600072
                       CODECHECK : 19088
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
--------------属性部分----------------
元语言类型: 中文
属性集个数: 2
--------------具体属性集----------------
**************************
属性集合名: 内容描述属性集合
属性集类别: 1    属性个数: 1
属性类别: 1    属性名: 内容标题
属性值: 江苏今年起实施“12311”计划 培育百个农业特色镇
------------------------------------
**************************
属性集合名: 内容管理属性集合
属性集类别: 15    属性个数: 1
属性类别: 15    属性名: 全UCL包数字签名
数字摘要算法: SHA-256   数字签名算法: DSA
摘要或签名信息: MCwCFBWoKM0ZNDi2o/B/L9TW2ey9hccaAhQVHMWDn6cX3HxCeLcpAVAmiqjrWg==
------------------------------------
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
--------------------------关联UCL结束-----------------------------
------------------------------------
属性类别: 15    属性名: 内容对象
属性值: 江苏今年起实施“12311”计划, 全省创意休闲农业工作推进会
------------------------------------
**************************
属性集合名: ZC目标对象编码体系属性集合
属性集类别: 2    属性个数: 11
属性类别: 1    属性名: 目标对象名称
名称: 战场
------------------------------------
属性类别: 2    属性名: 空间位置信息
坐标体系描述位置标准：GPS
位置坐标：北纬N39°40′20.09″ 东经E116°32′13.51
------------------------------------
属性类别: 3    属性名: 时间信息
授时信息规则：GPS
时间：Sun Jul 30 22:41:32 2017
------------------------------------
属性类别: 4    属性名: 目标外形
几何轮廓: 1, 长方形
投影边界: 北纬N39°40′20.09″ 东经E116°32′13.51
------------------------------------
属性类别: 5    属性名: 物理特性
电磁特性: 0, 反射电磁波
声波特性: , 反射声波
核生化特性: 1, 不产生核辐射
雷达特性: , 可被雷达检测
------------------------------------
属性类别: 6    属性名: 目标材质
材质: 1, 塑料材质
------------------------------------
属性类别: 7    属性名: 通过程度
通过程度: 1, 可通过
------------------------------------
属性类别: 8    属性名: 空间状况信息地
地面敌我状态信息: 坦克
空中敌我环境信息: 
水下敌我状况信息: 潜艇
------------------------------------
属性类别: 11    属性名: 绝对运动特性
运动特性解析信息: 速度单位为厘米每秒（cm/s），加速度单位为厘米每秒平方（cm/s2）
速度: 10
加速度: 
运动轨迹: 北纬N39°40′20.09″ 东经E116°32′13.51
------------------------------------
属性类别: 12    属性名: 相对运动特性
运动特性解析信息: 速度单位为厘米每秒（cm/s），加速度单位为厘米每秒平方（cm/s2）
速度: 10
加速度: 100
运动轨迹: 北纬N39°40′20.09″ 东经E116°32′13.51
------------------------------------
属性类别: 13    属性名: 运行轨迹
运动轨迹解析信息: GPS
运动轨迹: 10;;北纬N39°40′20.09″ 东经E116°32′13.51
------------------------------------
**************************
属性集合名: 内容管理属性集合
属性集类别: 15    属性个数: 2
属性类别: 12    属性名: 内容数字签名
数字摘要算法: SHA-512   数字签名算法: ECDSA
摘要或签名信息: MDUCGDiUiEwFPY8feTVwiLuDOS+Dse3VCpyrDgIZAKzEF1nV1EpvWq75aw/kmrmF94sc0EBjeg==
------------------------------------
属性类别: 15    属性名: 全UCL包数字签名
数字摘要算法: MD5   数字签名算法: RSA
摘要或签名信息: N26TVfQtDZyVyt1xHtIYAIylxElgFzDnu55m0axOskM33i2TjDHjanR5B+FF61MGdLtX19bFdYtgZ/I7TKBBqKKAocHRkbKHOKJR4MrkzhAjCCgx/cyr+JJP+0YQqYyUBCcqrvyNEkcwzTLHLeR+q3J1u0rbTz5Ungjv7c2dGLA=
------------------------------------
========== UCL test end==========
997
7
Process finished with exit code 0
```