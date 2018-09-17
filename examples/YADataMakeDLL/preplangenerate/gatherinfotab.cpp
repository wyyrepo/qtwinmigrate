#include "gatherinfotab.h"


GatherInfoTab::GatherInfoTab(QWidget *parent) : QWidget(parent)
{


   mainLayout = new QVBoxLayout;
   Layout =new QHBoxLayout;

   samplerate = new QLabel("采样率:", this);
   comboBox =new QComboBox(this);
   sampletime = new QLabel("采样时间", this);
   linedit1 = new QLineEdit(this);
   middle = new QLabel("---", this);
   linedit2 = new QLineEdit(this);
   query = new QPushButton("查询", this);
   retreat = new QPushButton("后退", this);
   play = new QPushButton("播放", this);
   advance = new QPushButton("前进", this);
//   QPushButton *quick =new QPushButton("下一个");




   comboBox->setMinimumWidth(200);

   Layout->addWidget(samplerate);
   Layout->addWidget(comboBox);
//   Layout->addStretch(1);


   Layout->addWidget(sampletime);
   Layout->addWidget(linedit1);
   Layout->addWidget(middle);
   Layout->addWidget(linedit2);
   Layout->addWidget(query);
   Layout->addWidget(retreat);
   Layout->addWidget(play);
   Layout->addWidget(advance);
//   Layout->addWidget(quick);
   Layout->addStretch(1);





   mainLayout->addLayout(Layout);
   mainLayout->addStretch(3);



   setLayout(mainLayout);

    iSerialNum = 0;



   connect(query, &QPushButton::clicked, this, [=](){
       STCCOMMAND stcCom;
       stcBFIQData stBFIQData;
       stBFIQData.cGZMS = 1;//启动播放IQ数据

       //命令类型
       stcCom.uhType = CMD_YASC;
       int iDatalen = 0;
       iDatalen = sizeof(stBFIQData);
       stcCom.pData = new unsigned char[iDatalen];
       memset( stcCom.pData, 0, iDatalen*sizeof(unsigned char) );
       memmove( stcCom.pData, &stBFIQData, iDatalen );
       stcCom.uiSerial = iSerialNum;
       iSerialNum++;
       if( iSerialNum == 2147483647 )//2147483647=2^32-1
       {
           iSerialNum = 0;
       }
       stcCom.uiLen = 10 + iDatalen;

       char * pSendBuf = NULL;
       int iSendLen = 0;
       int iPos = 0;
       iSendLen = 8 + stcCom.uiLen;
       pSendBuf = new char[iSendLen];
       memset( pSendBuf, 0, iSendLen );
       memmove( pSendBuf+iPos, &stcCom, 14 );
       iPos += 14;
       memmove( pSendBuf+iPos, stcCom.pData, iDatalen );
       iPos += iDatalen;
       memmove( pSendBuf+iPos, &stcCom.uiEnd, sizeof(int) );
       iPos += sizeof(int);

       //TCPSocket.SendDataClient( pSendBuf, iSendLen );
       emit sendDataClient( pSendBuf, iSendLen );

//       delete []stcCom.pData;
//       stcCom.pData = NULL;

//       delete []pSendBuf;
//       pSendBuf = NULL;
   });

}


