/*规定：所有角度值的单位均为“度”；
        方位角正北为零度；
		当俯仰角为零，车头、机头、导弹头等方位角为零，则为正北方向；
		雷达和光电的水平旋转方向由[方位最大扫描开始角]向[方位最大扫描结束角]顺时针旋转；
*/

#pragma once

// 战场环境
struct BattleEnvironment {
	short  terrain;				//	地形, 0-山地, 1-平原, 2-沙漠, 3-丘陵
	short  weather;				//	天气, 0-晴天, 1-少云, 2-中云, 3-多云, 4-小雨, 5-中雨, 6-大雨, 7-暴雨, 8-小雪, 9-中雪, 10-大雪, 11-暴雪
	double windSpeed;			//	风速, 单位：米/秒
	double windDirection;		//	风向, 单位：度
	double temperature;			//	温度, 单位：摄氏度
	double humidity;			//	湿度, 单位：百分比
	double barometricPressure;	//	气压, 单位：千帕	
	short  roadType;			//	路面类型, 0-沥青, 1-混凝土, 2-泥土
};

// 指挥系统
struct CommSys {
	int maxTarNum; 	// 最大目标分配数量
};

// 目指雷达
struct DirRadar {
	double	offsetx;				//	相对于指挥车的偏移x，单位：米
	double	offsety;				//	相对于指挥车的偏移y，单位：米
	double	offsetz;				//	相对于指挥车的偏移z，单位：米
	double	detectCycle;			//	扫描周期，单位：秒
	short	radarType;				//	雷达体制 0：机械；1：一维相控阵；2：二维相控阵
	double	detectAngYawStart;		//	方位最大扫描起始角，相对于车头的角度，单位：度
	double	detectAngYawStop;		// 	方位最大扫描结束角，相对于车头的角度，单位：度
	double	detectAngPitchStart;	// 	俯仰最大扫描起始角，单位：度
	double	detectAngPitchStop;		// 	俯仰最大扫描结束角，单位：度
	double	detectRangeYaw;			// 	波束大小，波束中切面夹角，单位：度
	double	fc;						// 	载频，单位：千兆赫兹 C波段(2~4GHz)；S波段(4~8GHz)
	double	detectRangeMax;			// 	参考威力范围，单位：米
	bool	typeMTI;				// 	使用MTI
	bool	typeMTD;				// 	使用MTD
};

// 火力系统
struct FireSys {
	double	offsetx;				//	相对于火力车的偏移x，单位：米
	double	offsety;				//	相对于火力车的偏移y，单位：米
	double	offsetz;				//	相对于火力车的偏移z，单位：米
	short	caliberGun;				//	火炮口径，单位：毫米
	short	numberGunBarrel;		//	身管数
	short	typeCarrier;			//	载体类型 0：自行履带；1：自行轮式；2：牵引
	short	methodLaunching;		//	发射方式 0：并行；1：串行；2：转管；3：转膛
	double	pitchAngGun;			//	火炮射界高低角中心线 单位：度
	double	pitchRangeGun;			//	火炮射界高低角范围 单位：度
	double	disRangeGun;			//	火炮火力范围 单位：米
	double	speedShootGun;			//	射速 单位：发/min	
	short	methodsShootLen;		//	射击长度 0：单发；1：短点射；2：长点射；3：连射
	short	shellNumNoShooting;		//	火炮弹量 单位：发
	short	typeShell;				//	火炮弹种 0：杀爆弹；1：脱壳穿甲弹；2：预置破片弹
	double	initialSpeedShell;		//	弹丸初速 单位：米/秒
	double	disRangeMis;			//	导弹火力范围 单位：米
	short	numMis;					//	导弹装弹数
	double	verOffsetAngMis;		//	导弹最大离轴方位角 单位：度
	double	horOffsetAngMis;		//	导弹俯仰角覆盖中心线 单位：度
	double	horOffsetAngRangeMis;	//	导弹俯仰角覆盖范围 单位：度
};

// 搜索雷达
struct SearchRadar {
	double	offsetx;				//	相对于指挥车的偏移x，单位：米
	double	offsety;				//	相对于指挥车的偏移y，单位：米
	double	offsetz;				//	相对于指挥车的偏移z，单位：米
	double	detectCycle;			//	扫描周期，单位：秒
	short	radarType;				//	雷达体制 0：机械；1：一维相控阵；2：二维相控阵
	double	detectAngYawStart;		//	方位最大扫描起始角，相对于车头的角度，单位：度
	double	detectAngYawStop;		//	方位最大扫描结束角，相对于车头的角度，单位：度
	double	detectAngPitchStart;	//	俯仰最大扫描起始角，单位：度
	double	detectAngPitchStop;		//	俯仰最大扫描结束角，单位：度
	double	detectRangeYaw;			//	波束大小，单位：度
	double	fc;						// 	载频，单位：千兆赫兹 C波段(2~4GHz)；S波段(4~8GHz)
	double	detectRangeMax;			//	参考威力范围，单位：米
	bool	typeMTI;				//	使用MTI
	bool	typeMTD;				//	使用MTD
};

// 跟踪雷达
struct TrackRadar{
	double	offsetx;				//	相对于指挥车的偏移x，单位：米
	double	offsety;				//	相对于指挥车的偏移y，单位：米
	double	offsetz;				//	相对于指挥车的偏移z，单位：米
	short	radarType;				//	雷达体制 0：机械；1：一维相控阵；2：二维相控阵
	double	detectAngYawStart;		//	方位最大扫描起始角，相对于车头的角度，单位：度
	double	detectAngYawStop;		//	方位最大扫描结束角，相对于车头的角度，单位：度
	double	detectAngPitchStart;	//	俯仰最大扫描起始角，单位：度
	double	detectAngPitchStop;		//	俯仰最大扫描结束角，单位：度	
	double	detectRangeYaw;			//	波束大小，单位：度
	double	fc;						//	载频, 单位：千兆赫兹, Ka波段(27-40GHz)
	double	detectRangeMax;			//	参考威力范围，单位：米
	bool	typeMTI;				//	使用MTI
	bool	typeMTD;				//	使用MTD
	double	turnAzVel;				//	方位转动角速度，单位：度/秒
	double	turnElVel;				//	俯仰转动角速度，单位：度/秒
	double	turnAzAcc;				//	方位转动角加速度，单位：度/秒平方
	double	turnElAcc;				//	俯仰转动角加速度，单位：度/秒平方
	double	turnAzError;			//	方位伺服跟踪精度，单位：度
	double	turnElError;			//	俯仰伺服跟踪精度，单位：度
};

// 光电跟踪
struct PhotTrack{
	double	offsetx;					//	相对于指挥车的偏移x，单位：米
	double	offsety;					//	相对于指挥车的偏移y，单位：米
	double	offsetz;					//	相对于指挥车的偏移z，单位：米
	double	detectAngYawStart;			//	方位最大扫描起始角，相对于车头的角度，单位：度
	double	detectAngYawStop;			//	方位最大扫描结束角，相对于车头的角度，单位：度
	double	detectAngPitchStart;		//	俯仰最大扫描起始角，单位：度
	double	detectAngPitchStop;			//	俯仰最大扫描结束角，单位：度
	double	detectAngRangeYaw;			//	波束大小，单位：度
	double	detectAngSpeedMaxPitch;		//	最大跟踪高低角速度，单位：度/秒
	double	detectAngAccMaxPitch;		//	最大跟踪高低角加速度，单位：度/秒平方
	double	detectAngSpeedMaxYaw;		//	最大跟踪方位角速度，单位：度/秒
	double	detectAngAccMaxYaw;			//	最大跟踪方位角加速度，单位：度/秒平方
	double	detectRangeMax;				//	威力范围，单位：米
	double	servoPre;					//	伺服跟踪精度，单位：度
	bool	laserWork;					//	激光测距
	double	laserDisPre;				//	激光测距精度，单位：米
};

// 固定翼飞机
struct FixedWing{
	double lon;				//	经度
	double lat;				//	纬度
	double alt;				//	高度
	double yaw;				//	方位角
	double pitch;			//	俯仰角
	double roll;			//	滚转角
	double rcs;				//	RCS, 单位：平方米
	short  rcsType;			//	RCS起伏类型, 0-swerling0, 1-swerling1, 2-swerling2, 3-swerling3, 4-swerling4
	double length;			//	机长, 单位：米
	double width;			//	翼展, 单位：米
	double height;			//	机高, 单位：米
	bool   interfereFlag;	//	有源压制干扰, 0-无， 1-有
	double carrierFrequency;//	载频, 单位：兆赫兹
	double bandwidth;		//	带宽, 单位：兆赫兹
	double power;			//	功率, 单位：分贝毫瓦
};

// 直升机
struct Helicopter{
	double lon;				//	经度
	double lat;				//	纬度
	double alt;				//	高度
	double yaw;				//	方位角
	double pitch;			//	俯仰角
	double roll;			//	滚转角
	double rcs;				//	RCS, 单位：平方米
	short  rcsType;			//	RCS起伏类型, 0-swerling0, 1-swerling1, 2-swerling2, 3-swerling3, 4-swerling4
	double length;			//	机长, 单位：米
	double width;			//	翼展, 单位：米
	double height;			//	机高, 单位：米
	bool   interfereFlag;	//	有源压制干扰, 0-无， 1-有
	double carrierFrequency;//	载频, 单位：兆赫兹
	double bandwidth;		//	带宽, 单位：兆赫兹
	double power;			//	功率, 单位：分贝毫瓦
};

// 无人机
struct UAV{
	double lon;				//	经度
	double lat;				//	纬度
	double alt;				//	高度
	double yaw;				//	方位角
	double pitch;			//	俯仰角
	double roll;			//	滚转角
	double rcs;				//	RCS, 单位：平方米
	short  rcsType;			//	RCS起伏类型, 0-swerling0, 1-swerling1, 2-swerling2, 3-swerling3, 4-swerling4
	double length;			//	机长, 单位：米
	double width;			//	翼展, 单位：米
	double height;			//	机高, 单位：米
	bool   interfereFlag;	//	有源压制干扰, 0-无， 1-有
	double carrierFrequency;//	载频, 单位：兆赫兹
	double bandwidth;		//	带宽, 单位：兆赫兹
	double power;			//	功率, 单位：分贝毫瓦
};

// 巡航导弹
struct CruiseMissile{
	double lon;				//	经度
	double lat;				//	纬度
	double alt;				//	高度
	double yaw;				//	方位角
	double pitch;			//	俯仰角
	double roll;			//	滚转角
	double rcs;				//	RCS, 单位：平方米
	short  rcsType;			//	RCS起伏类型, 0-swerling0, 1-swerling1, 2-swerling2, 3-swerling3, 4-swerling4
	double length;			//	机长, 单位：米
	double width;			//	翼展, 单位：米
	double height;			//	机高, 单位：米
};

// 精确制导炸弹
struct GuidedBomb{
	double lon;				//	经度
	double lat;				//	纬度
	double alt;				//	高度
	double yaw;				//	方位角
	double pitch;			//	俯仰角
	double roll;			//	滚转角
	double rcs;				//	RCS, 单位：平方米
	short  rcsType;			//	RCS起伏类型, 0-swerling0, 1-swerling1, 2-swerling2, 3-swerling3, 4-swerling4
	double length;			//	机长, 单位：米
	double width;			//	翼展, 单位：米
	double height;			//	机高, 单位：米
};