/*cmdrsp.h*/
/*Copyright 2017-2027 PLA6909.*/
/*
modification history
--------------------
20170802,CL  written.
2017, CL modified.
*/
#ifndef __CMDRSP_H__
#define __CMDRSP_H__

#ifdef __cplusplus
extern "C" {
#endif

#define MHZ	1000000
#define TenKHZ	10000
#define KHZ	1000

/////////////////////////////////////////////////////////////////////////////
//      控制命令码定义
/////////////////////////////////////////////////////////////////////////////
#define CMD_BITE		(0x0100)	/* 自检	控制卫星信号在线分析服务进行设备自检工作，并将设备自检结果上报给卫星信号侦察控制软件显示 */
#define CMD_LINK		(0x0101)	/* 链路检查	用于通信信号采集与分析系统内客户端与服务端软件之间连接状态查询 */
#define CMD_WBBJPP		(0x0102)	/* 建立频谱背景 控制卫星信号在线分析服务建立背景频谱数据，用于宽带信号搜索分析 */
#define CMD_WBSS		(0x0103)	/* 宽带搜索	控制卫星信号在线分析服务进行宽带搜索、分析、采集存储等工作，并将宽带搜索的频谱数据、信号分析结果等数据上报给卫星信号侦察控制软件显示 */
#define CMD_NBKS		(0x0104)	/* 窄带控守	控制卫星信号在线分析服务进行窄带信号检测、信号参数测量、信号调制识别、信号解调、信号解码等工作，采集工作，并将窄带信号分析结果、频谱图、符号率图、解调音频数据、解调码流数据、星座图数据、一次方频谱图、二次方频谱图、四次方频谱图等数据上报给卫星信号侦察控制软件显示 */
#define CMD_YASC		(0x0105)	/* 预案生成	控制卫星信号在线分析服务播放指定IQ数据、生成预案数据、播放预案数据 */


//设备地址定义
#define DEVADDRESS_SEAT	0x1C1C//席位计算机地址：0x1C1C
#define DEVADDRESS_ProCess	0x4C4C//处理机地址：0x4C4C


/////////////////////////////////////////////////////////////////////////////
//      结构定义, 含数据内容
/////////////////////////////////////////////////////////////////////////////

#pragma pack(1)

//报文格式
typedef struct stcCommand
{
    stcCommand()
    {
        uiStart = 0x7E7E7E7E;
        uiLen = 16;
        //uhDest = 0x1C1C;
        //uhScr = 0x4C4C;
        //ucPrVer = 1;
        //ucPrID = 1;
        uhType = 0;
        uiSerial = 0;
        pData = NULL;
        uiEnd = 0x0A0D0A0D;
    }

    unsigned int uiStart;	//命令起始码,固定为0x7E7E7E7E;
    unsigned int uiLen;		//报文长度，包括从报文长度字段到数据包的总字节数
//	unsigned short uhDest;	//目的地址，席位计算机地址：0x1C1C；处理机地址：0x4C4C
//	unsigned short uhScr;	//源地址，席位计算机地址：0x1C1C；处理机地址：0x4C4C
//	unsigned char ucPrVer;	//协议版本,置为1
//	unsigned char ucPrID;	//协议ID，置为1
    unsigned short uhType;	//控制命令码
    unsigned int uiSerial;	//流水号
    unsigned char * pData;	//数据包
    unsigned int uiEnd;		//命令终止码,固定为0x0A0D0A0D;
}STCCOMMAND;

//1.自检
//1.1.启动自检报文
typedef struct stcSelfCheck_Start
{
    stcSelfCheck_Start()
    {
        uiDataType = 1;
        uiBaoLiu = 0;
    }
    unsigned int uiDataType;	//数据包属性,1:表示启动
    unsigned int uiBaoLiu;		//保留
}STCSELFCHECK_START;

//1.2.启动自检上报结果报文
typedef struct stcSelfCheck_Result
{
    stcSelfCheck_Result()
    {
        uiDataType = 0x1000;
        uiResultCJFXK = 1;
        uiResultGTCCDY1 = 1;
        uiResultGTCCDY2 = 1;
        uiResultXHCLK = 1;
        uiResultKZJSJK = 1;
    }

    unsigned int uiDataType;	//数据包属性,0x1000，表示自检结果
    unsigned int uiResultCJFXK;	//采集分析卡自检结果，1:正常,0:故障
    unsigned int uiResultGTCCDY1;//固态存储单元1自检结果，1:正常,0:故障
    unsigned int uiResultGTCCDY2;//固态存储单元2自检结果，1:正常,0:故障
    unsigned int uiResultXHCLK;	 //信号处理卡自检结果，1:正常,0:故障
    unsigned int uiResultKZJSJK; //控制计算机卡自检结果，1:正常,0:故障
}STCSELFCHECK_RESULT;


//2.链路检查
//2.1.启动链路检查报文
typedef struct stcLink_Start
{
    stcLink_Start()
    {
        uiDataType = 1;
        uiBaoLiu = 0;
    }

    unsigned int uiDataType;	//数据包属性,1:表示启动
    unsigned int uiBaoLiu;//保留
}STCLINK_START;

//2.2.启动链路检查回执报文
typedef struct stcLink_StartReturn
{
    stcLink_StartReturn()
    {
        uiDataType = 2;
        uiFunction = 1;
    }

    unsigned int uiDataType;	//数据包属性,2:表示启动回执
    unsigned int uiFunction;	//功能是否正常启动，1：正常， 0：故障
}STCLINK_STARTRETURN;


//3.建立背景频谱
//3.1.启动建立频谱背景报文
typedef struct stcWBBJPP_Start
{
    stcWBBJPP_Start()
    {
        uiDataType = 1;
        dStartFreq = 300000;
        dEndFreq = 400000;
        uiZS = 5;
        uiFFTNum = 2048;
        uiBaoLiu = 0;
    }

    unsigned int uiDataType;	//数据包属性,1:表示启动建立频谱背景
    double dStartFreq;//起始频率,单位为Khz
    double dEndFreq;//终止频率,单位为Khz
    unsigned int uiZS;//帧数
    unsigned int uiFFTNum;//FFT点数
    unsigned int uiBaoLiu;//保留
}STCWBBJPP_START;

//3.2.背景频谱数据报文
typedef struct stcWBBJPP_Result
{
    stcWBBJPP_Result()
    {
        uiDataType = 0x1001;
        dStartFreq = 300000;
        dEndFreq = 400000;
        uiFFTNum = 2048;
        phLevel = NULL;
    }

    unsigned int uiDataType;	//数据包属性,0x1001，背景频谱数据
    double dStartFreq;//起始频率,单位为Khz
    double dEndFreq;//终止频率,单位为Khz
    unsigned int uiFFTNum;//FFT点数
    short * phLevel;//电平值,单位dBm
}STCWBBJPP_RESULT;

//3.3.停止建立背景频谱数据报文
typedef struct stcWBBJPP_Stop
{
    stcWBBJPP_Stop()
    {
        uiDataType = 2;
        dStartFreq = 300000;
        dEndFreq = 400000;
        uiBaoLiu = 0;
    }

    unsigned int uiDataType;	//数据包属性,2,表示停止建立频谱背景
    double dStartFreq;//起始频率,单位为Khz
    double dEndFreq;//终止频率,单位为Khz
    unsigned int uiBaoLiu;//保留
}STCWBBJPP_STOP;


//4.宽带搜索
//4.1.启动宽带搜索报文
//非法信号参数结构体(即客户端界面的自动采集频率列表的信号参数信息)
typedef struct stcffxh_Param
{
    stcffxh_Param()
    {
        dFreq = 300000;
        dDK = 150;
        memset( cModulate, 0, 8 );
    }
    double dFreq;//频率值,单位khz
    double dDK;//带宽值,单位khz
    char cModulate[8];//调制样式
}STCFFXH_PARAM;

typedef struct stcWBSearch_Start
{
    stcWBSearch_Start()
    {
        uiDataType = 1;
        dStartFreq_JC = 300000;//检测起始频率,单位为Khz
        dEndFreq_JC = 400000;//检测终止频率,单位为Khz
        ucSPAtten = 0;//射频衰减,255：自动衰减(即预选放大)，其他表示手动衰减。
        ucZY = 0;//增益，255：自动增益，其他表示手动增益。
        ucIfFX = 0;//是否分析,0：不分析，1：分析
        dStartFreq_FX = 300000;//分析起始频率,单位为Khz
        dEndFreq_FX = 400000;//分析终止频率,单位为Khz
        ucIfCC = 0;//是否存储,0：不存储，1：存储
        ucCCMS = 1;//存储模式,0：按时间存储 1：按大小存储
        uiCCCXSJ = 10;//存储持续时间,单位s
        uiCCDX = 1000;//存储大小,单位MB
        uiFFXHNum = 10;//存储匹配非法频率集数量,假设为n
        pFFXH_Param = NULL;
        uiBaoLiu = 0;
    }

    unsigned int uiDataType;	//数据包属性,1:表示启动
    double dStartFreq_JC;//检测起始频率,单位为Khz
    double dEndFreq_JC;//检测终止频率,单位为Khz
    unsigned char ucSPAtten;//射频衰减,255：自动衰减(即预选放大)，其他表示手动衰减。
    unsigned char ucZY;//增益，255：自动增益，其他表示手动增益。
    unsigned char ucIfFX;//是否分析,0：不分析，1：分析
    double dStartFreq_FX;//分析起始频率,单位为Khz
    double dEndFreq_FX;//分析终止频率,单位为Khz
    unsigned char ucIfCC;//是否存储,0：不存储，1：存储
    unsigned char ucCCMS;//存储模式,0：按时间存储 1：按大小存储
    unsigned int uiCCCXSJ;//存储持续时间,单位s
    unsigned int uiCCDX;//存储大小,单位MB
    unsigned int uiFFXHNum;//存储匹配非法频率集数量,假设为n
    STCFFXH_PARAM * pFFXH_Param;

    unsigned int uiBaoLiu;//保留，可增加参数
}STCWBSEARCH_START;

//4.2.启动宽带搜索上报结果
//4.2.1.启动宽带搜索上报频谱数据
typedef struct stcWBSearch_ReportPinPu
{
    stcWBSearch_ReportPinPu()
    {
        uiDataType = 0x1003;
        dStartFreq_JC = 300000;
        dEndFreq_JC = 400000;
        uiFFTNum = 2048;
        phLevel = NULL;
    }

    unsigned int uiDataType;//数据包属性,0x1003，宽带频谱数据
    double dStartFreq_JC;//检测起始频率,单位为Khz
    double dEndFreq_JC;//检测终止频率,单位为Khz
    unsigned int uiFFTNum;//FFT点数
    short * phLevel;//电平值,单位dBm
}STCWBSEARCH_REPORTPINPU;

//4.2.2.启动宽带搜索上报宽带搜索信号结果
typedef struct SigleResult
{
    SigleResult()
    {
        dFreq = 300000;
        dDK = 200;
        hLevel = 0;
        hXZB = 30;
        dTZSL = 100;
        memset( cModulate, 0, sizeof(cModulate) );
        memset( cBMFS, 0, sizeof(cBMFS) );
        memset( cAppearTime, 0, sizeof(cAppearTime) );
        uiXHCXSJ = 1200;
    }
    double  dFreq;//信号频率，单位KHz
    double  dDK;//信号带宽，单位KHz
    short hLevel;//电平值,单位dBm
    short hXZB;//信噪比,单位dB
    double dTZSL;//调制速率,单位Ksps
    char cModulate[8];//调制样式
    char cBMFS[8];//编码方式
    char cAppearTime[12];//信号出现时间
    unsigned int uiXHCXSJ;//信号持续时间,单位ms
}SIGLERESULT;

typedef struct stcWBSearch_ReportSigResult
{
    stcWBSearch_ReportSigResult()
    {
        uiDataType = 0x1004;
        dStartFreq_FX = 300000;
        dEndFreq_FX = 400000;
        uiSigNum = 1024;
        pstcSigResult = NULL;
    }

    unsigned int uiDataType;	//数据包属性,0x1004，宽带搜索信号结果
    double dStartFreq_FX;//分析起始频率,单位为kHz
    double dEndFreq_FX;//分析终止频率,单位为kHz
    unsigned int uiSigNum;//所包含的目标信号个数(n)
    SIGLERESULT * pstcSigResult;
}STCWBSEARCH_REPORTSIGRESULT;

//4.3.停止宽带搜索报文
typedef struct stcWBSearch_Stop
{
    stcWBSearch_Stop()
    {
        uiDataType = 2;
        dStartFreq_JC = 300000;
        dEndFreq_JC = 400000;
        uiBaoLiu = 0;
    }

    unsigned int uiDataType;//数据包属性,2:表示停止
    double dStartFreq_JC;//检测起始频率,单位为kHz
    double dEndFreq_JC;//检测终止频率,单位为kHz
    unsigned int uiBaoLiu;//保留
}STCWBSEARCH_STOP;



//5.窄带控守
//5.1.启动窄带控守报文
typedef struct ChannelParam
{
    ChannelParam()
    {
        ucGZMS = 0;
        ucKSMS = 1;
        ucIfJMa = 0;
        ucIfJMi = 0;
        dFreq = 300000;
        dDK = 150;
        memset( cModulate, 0, sizeof(cModulate) );
        dFHL = 500;
        memset( cBMFS, 0, sizeof(cBMFS) );
        memset( cJMFS, 0, sizeof(cJMFS) );
    }
    unsigned char ucGZMS;//工作模式,0：停止，1：启动
    unsigned char ucKSMS;//控守模式,0：实时分析解调， 1：实时分析
    unsigned char ucIfJMa;//是否解码,0：不解，1：解
    unsigned char ucIfJMi;//是否解密,0：不解，1：解
    double dFreq;//频率,单位:kHz
    double dDK;//带宽,单位:kHz
    char cModulate[8];//解调方式
    double dFHL;//符号率
    char cBMFS[16];//编码方式
    char cJMFS[16];//加密方式
}CHANNELPARAM;

typedef struct stcNBKS_Start
{
    stcNBKS_Start()
    {
        uiDataType = 1;
        uiCYL = 70;
        uiFFTNum = 2048;
        uiChannelNum = 1;
        pChannelParam = NULL;
        memset( uiBaoLiu, 0, sizeof(uiBaoLiu) );
    }

    unsigned int uiDataType;	//数据包属性,1，表示启动窄带控守
    unsigned int uiCYL;//采样率,单位:MHz
    unsigned int uiFFTNum;//FFT点数
    unsigned int uiChannelSL;//通道数量,侦察控制软件界面上有4个窄带通道
    unsigned int uiChannelNum;//通道编号,侦察控制软件界面上4个窄带通道编号为1,2,3,4
    CHANNELPARAM * pChannelParam;

    unsigned int uiBaoLiu[3];//保留，可增加参数
}STCNBKS_START;

//5.2.启动窄带控守上报结果
//5.2.1.窄带控守频谱数据报文
typedef struct stcNBKS_PinPu
{
    stcNBKS_PinPu()
    {
        uiDataType = 0x1005;
        uiChannelNum = 1;
        dFreq = 300000;
        uiFFTNum = 2048;
        pLevel = NULL;
    }

    unsigned int uiDataType;//数据包属性,0x1005，窄带控守频谱数据
    unsigned int uiChannelNum;//通道编号,侦察控制软件界面上4个窄带通道编号为1,2,3,4
    double dFreq;//频率,单位:kHz
    unsigned int uiFFTNum;//FFT点数
    short * pLevel;//电平,单位:dBm,电平的点数由FFT点数决定
}STCNBKS_PINPU;

//5.2.2.窄带控守信号分析结果数据
typedef struct stcNBKS_SigResult
{
    stcNBKS_SigResult()
    {
        uiDataType = 0x1006;
        uiChannelNum = 1;
        dFreq = 300000;
        dDK = 150;
        hLevel = -15;
        hXZB = 30;
        dTZSL = 150;
        memset( cModulate, 0, sizeof(cModulate) );
        memset( cBMFS, 0, sizeof(cBMFS) );
        memset( cCapTime, 0, sizeof(cCapTime) );
        uiCXSJ = 1000;
    }

    unsigned int uiDataType;//数据包属性,0x1006，窄带控守信号分析结果
    unsigned int uiChannelNum;//通道编号,侦察控制软件界面上4个窄带通道编号为1,2,3,4
    double dFreq;//频率,单位为kHz
    double dDK;//带宽,单位为kHz
    short hLevel;//电平,单位dBm
    short hXZB;//信噪比,单位为db
    double dTZSL;//调制速率,单位为Ksps
    char cModulate[8];//调制样式
    char cBMFS[8];//编码方式
    char cCapTime[12];//截获时间
    unsigned int uiCXSJ;//持续时间,单位ms

}STCNBKS_SIGRESULT;

//5.2.3.窄带控守信号解码结果数据
typedef struct stcNBKS_JMaResult
{
    stcNBKS_JMaResult()
    {
        uiDataType = 0x1007;
        uiChannelNum = 1;
        dFreq = 300000;
        uiMaLiuLen = 2048;
        pMaLiu = NULL;
    }

    unsigned int uiDataType;//数据包属性,0x1007，信号解码结果
    unsigned int uiChannelNum;//通道编号,侦察控制软件界面上4个窄带通道编号为1,2,3,4
    double dFreq;//频率,单位为kHz
    unsigned int  uiMaLiuLen;//码流长度
    unsigned char * pMaLiu;//码流字符
}STCNBKS_JMARESULT;

//5.2.4.窄带控守符号率图数据
typedef struct stcNBKS_FHLTData
{
    stcNBKS_FHLTData()
    {
        uiDataType = 0x1008;
        uiChannelNum = 1;
        dFreq = 300000;
        uiFHSL = 150;
        uiFHLTLen = 1024;
        pFHLData = NULL;
    }

    unsigned int uiDataType;//数据包属性,0x1008，符号率图数据
    unsigned int uiChannelNum;//通道编号,侦察控制软件界面上4个窄带通道编号为1,2,3,4
    double dFreq;//频率,单位为kHz
    unsigned int  uiFHSL;//符号速率,单位为kHz
    unsigned int  uiFHLTLen;//符号率图形数据个数
    int  * pFHLData;//符号率图形数据
}STCNBKS_FHLTDATA;

//5.2.5.窄带控守解调音频数据
typedef struct stcNBKS_Audio
{
    stcNBKS_Audio()
    {
        uiDataType = 0x1009;
        uiChannelNum = 1;
        dFreq = 300000;
        uiYPCYL = 8000;
        uiYPLen = 2048;
        pYPData = NULL;
    }

    unsigned int uiDataType;//数据包属性,0x1009，解调音频数据
    unsigned int uiChannelNum;//通道编号,侦察控制软件界面上4个窄带通道编号为1,2,3,4
    double dFreq;//频率,单位为kHz
    unsigned int  uiYPCYL;//音频采样率,单位为kHz，数据为16bit
    unsigned int  uiYPLen;//音频数据个数
    int  * pYPData;//音频数据

}STCNBKS_AUDIO;

//5.2.6.窄带控守解调码流数据
typedef struct stcNBKS_MaLiu
{
    stcNBKS_MaLiu()
    {
        uiDataType = 0x2000;
        uiChannelNum = 1;
        dFreq = 300000;
        uiMLLen = 2048;
        pMLData = NULL;
    }

    unsigned int uiDataType;//数据包属性,0x2000，信号解调码流结果
    unsigned int uiChannelNum;//通道编号,侦察控制软件界面上4个窄带通道编号为1,2,3,4
    double dFreq;//频率,单位为kHz
    unsigned int  uiMLLen;//码流数据长度
    unsigned char  * pMLData;//码流字符

}STCNBKS_MALIU;

//5.2.7.窄带控守解调星座图数据
typedef struct stcNBKS_XZT
{
    stcNBKS_XZT()
    {
        uiDataType = 0x2001;
        uiChannelNum = 1;
        dFreq = 300000;
        uiXZTLen = 2048;
        pXZTData = NULL;
    }

    unsigned int uiDataType;//数据包属性,0x2001，解调星座图数据
    unsigned int uiChannelNum;//通道编号,侦察控制软件界面上4个窄带通道编号为1,2,3,4
    double dFreq;//频率,单位为kHz
    unsigned int  uiXZTLen;//星座图数据个数
    int  * pXZTData;//星座图数据

}STCNBKS_XZT;

//5.2.8.窄带控守一次方谱图数据
typedef struct stcNBKS_YCFT
{
    stcNBKS_YCFT()
    {
        uiDataType = 0x2002;
        uiChannelNum = 1;
        dFreq = 300000;
        uiFFTLen = 2048;
        pLevel = NULL;
    }

    unsigned int uiDataType;//数据包属性,0x2002，一次方频谱数据
    unsigned int uiChannelNum;//通道编号,侦察控制软件界面上4个窄带通道编号为1,2,3,4
    double dFreq;//频率,单位为kHz
    unsigned int  uiFFTLen;//FFT点数
    short  * pLevel;//电平数据,单位为dBm

}STCNBKS_YCFT;

//5.2.9.窄带控守二次方谱图数据
typedef struct stcNBKS_ECFT
{
    stcNBKS_ECFT()
    {
        uiDataType = 0x2003;
        uiChannelNum = 1;
        dFreq = 300000;
        uiFFTLen = 2048;
        pLevel = NULL;
    }

    unsigned int uiDataType;//数据包属性,0x2003，二次方频谱数据
    unsigned int uiChannelNum;//通道编号,侦察控制软件界面上4个窄带通道编号为1,2,3,4
    double dFreq;//频率,单位为kHz
    unsigned int  uiFFTLen;//FFT点数
    short  * pLevel;//电平数据,单位为dBm

}STCNBKS_ECFT;

//5.2.10.窄带控守四次方谱图数据
typedef struct stcNBKS_SCFT
{
    stcNBKS_SCFT()
    {
        uiDataType = 0x2004;
        uiChannelNum = 1;
        dFreq = 300000;
        uiFFTLen = 2048;
        pLevel = NULL;
    }

    unsigned int uiDataType;//数据包属性,0x2004，四次方频谱数据
    unsigned int uiChannelNum;//通道编号,侦察控制软件界面上4个窄带通道编号为1,2,3,4
    double dFreq;//频率,单位为kHz
    unsigned int  uiFFTLen;//FFT点数
    short  * pLevel;//电平数据,单位为dBm

}STCNBKS_SCFT;

//5.3.停止窄带控守报文
typedef struct stcNBKS_Stop
{
    stcNBKS_Stop()
    {
        uiDataType = 2;
        uiBaoLiu = 0;
    }

    unsigned int uiDataType;//数据包属性,2，表示停止窄带控守
    unsigned int uiBaoLiu;//保留，4字节对齐
}STCNBKS_STOP;



//6.预案生成
//6.1.播放指定IQ数据报文
typedef struct stcBFIQData
{
    stcBFIQData()
    {
        uiDataType = 1;
        cGZMS = 0;
        uiFFTNum = 2048;
        dFreq = 300000;
        dDK = 150;
        memset( cCJStartTime, 0, sizeof(cCJStartTime) );
        memset( cCJEndTime, 0, sizeof(cCJEndTime) );
        uiCYL = 8000;
        uiCJDataLen = 1000;
        memset( cCJDataAdd, 0, sizeof(cCJDataAdd) );
    }

    unsigned int uiDataType;//数据包属性,1:表示启动
    char cGZMS;//工作模式,0：停止，1：启动
    unsigned int uiFFTNum;//FFT点数
    double dFreq;//中频频率，单位：kHz
    double dDK;//带宽,单位：kHz
    char cCJStartTime[12];//采集开始时间
    char cCJEndTime[12];//采集结束时间
    unsigned int uiCYL;//采样率,单位:kHz
    unsigned int uiCJDataLen;//采集数据大小
    char cCJDataAdd[12];//采集数据地址
}STCBFIQDATA;

//6.2.预案频谱数据报文
typedef struct stcYAPinPuData
{
    stcYAPinPuData()
    {
        uiDataType = 0x2005;
        dStartFreq = 300000;
        dEndFreq = 400000;
        uiFFTNum = 2048;
        pLevel = NULL;
    }

    unsigned int uiDataType;//数据包属性,0x2005，预案频谱数据
    double dStartFreq;//起始频率，单位:kHz
    double dEndFreq;//终止频率，单位:kHz
    unsigned int uiFFTNum;//FFT点数
    short * pLevel;//电平数据,单位dBm
}STCYAPINPUDATA;

//6.3.生成预案数据命令报文
typedef struct stcYADataCommand
{
    stcYADataCommand()
    {
        uiDataType = 2;
        memset( cStartTime, 0, sizeof(cStartTime) );
        memset( cEndTime, 0, sizeof(cEndTime) );
        dStartFreq = 300000;
        dEndFreq = 400000;
    }

    unsigned int uiDataType;//数据包属性,2，表示生成预案数据命令
    char cStartTime[12];//开始时间
    char cEndTime[12];//结束时间
    double dStartFreq;//开始频率,单位:kHz
    double dEndFreq;//结束频率,单位:kHz

}STCYADATACOMMAND;

//6.4.生成预案数据回执报文
typedef struct stcYADataCommand_Return
{
    stcYADataCommand_Return()
    {
        uiDataType = 3;
        memset( cYADataFilePath, 0, sizeof(cYADataFilePath) );
        cStatus = 0;
        memset( cFail, 0, sizeof(cFail) );
    }

    unsigned int uiDataType;//数据包属性,3，表示生成预案数据回执
    char cYADataFilePath[256];//预案IQ数据文件路径
    char cStatus;//生成状态,0:失败1：成功
    char cFail[256];//失败原因

}STCYADATACOMMAND_RETURN;

//6.5.播放预案数据命令报文
typedef struct stcBFYADataCommand
{
    stcBFYADataCommand()
    {
        uiDataType = 4;
        cGZMS = 0;
        memset( cYAFilePath, 0, sizeof(cYAFilePath) );
        cBFMS = 0;
    }

    unsigned int uiDataType;//数据包属性,4，表示播放预案数据命令
    char cGZMS;//工作模式,0：停止播放1：启动播放
    char cYAFilePath[256];//预案文件路径
    char cBFMS;//播放模式,0：循环播放，1：顺序播放
}STCBFYADATACOMMAND;

//6.6.播放预案数据回执报文
typedef struct stcBFYADataCommand_Return
{
    stcBFYADataCommand_Return()
    {
        uiDataType = 5;
        cZFStatus = 0;
        cBFStatus = 0;
    }

    unsigned int uiDataType;//数据包属性,5，表示播放预案数据回执
    char cZFStatus;//转发数据状态，0:未完成1：完成
    char cBFStatus;//播放数据状态，0:未完成1：完成

}STCBFYADATACOMMAND_RETURN;



#pragma pack()


#ifdef __cplusplus
}
#endif
#endif /* __CMDRSP_H__ */
