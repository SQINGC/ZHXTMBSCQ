
/******************************************************************************/

// 态势装订数据分两次下发
// 第一步：下发想定基本信息及节点基本信息和节点绑定信息
// 第二步：下发各节点初始化数据

// 主控选择态势文件解析后，进行第一步

// 第一步数据包格式如下：
// 包头的消息类型为 COMMAND（2），指令类型为 CommondSituInit（5）
// 包体内容为 
// 态势ID|仿真步长|原点坐标;
// 节点ID1|分配的数据ID1,分配的数据ID2;
// 节点ID2|分配的数据ID1,分配的数据ID2;
// .....@
// 实体类型(指、火、火主、火附属)|实体ID|经度,纬度,高度,方位,俯仰,滚转|关联数据ID1,关联数据ID2,关联数据ID3,关联数据ID4|关联实体ID;
// .....
// 注：载体节点关联数据ID数量最大值为4，若不存在则为-1，非载体节点根据自身数据ID到载体节点中进行查找，确认载体位置

// 例：25|20|120,39,700;401|40101,40102;501|50101,50102;.....

// 各节点收到第一步的数据包后发送应答指令，应答指令包头的消息类型为 COMMAND（2），指令类型为 CommondSituInitReturn（6）
// 主控节点收到所有节点的应答指令后，进行第二步数据下发

// 第二步数据包格式如下：
// 包头的消息类型为 COMMAND（2），指令类型为 CommondSituBind（7）
// 包体内容为 “初始化数据ID+初始化结构体”,初始化数据ID为4字节整型

// 各节点收到第二步的数据包后发送应答指令，应答指令包头的消息类型为COMMAND（2），指令类型为CommandSituBindReturn（8）

/******************************************************************************/
/*
// 战场环境
struct BattleEnvironment {
	short Terrain;				//	地形, 0-山地, 1-平原, 2-沙漠, 3-丘陵
	short Weather;				//	天气, 0-晴天, 1-少云, 2-中云, 3-多云, 4-小雨, 5-中雨, 6-大雨, 7-暴雨, 8-小雪, 9-中雪, 10-大雪, 11-暴雪
	double WindSpeed;			//	风速, 米/秒
	double WindDirection;		//	风向, 度
	double Temperature;			//	温度, 摄氏度
	double Humidity;			//	湿度, 百分比
	double BarometricPressure;	//	气压, 兆帕	
	short RoadType;				//	路面类型, 0-沥青, 1-混凝土, 2-泥土
};

// 指挥车
struct CommCar {
	double lon;		//	经度
	double lat;		//	纬度
	double alt;		//	高度
	double yaw;		//	方位角
	double pitch;	//	俯仰角
	double roll;	//	滚转角
};

// 指挥系统
struct CommSys {
	int MaxTarNum; 	// 最大目标分配数量
};

// 目指雷达
struct DirRadar {
	double	Offset_x;			//	相对于指挥车的偏移x，单位：米
	double	Offset_y;			//	相对于指挥车的偏移y，单位：米
	double	Offset_z;			//	相对于指挥车的偏移z，单位：米
	short	DetectCycle;		//	扫描周期，单位：秒
	short	RadarType;			//	雷达体制 0：机械；1：一维相控阵；2：二维相控阵
	double	DetectAng_Yaw_Start;//	方位最大扫描中心角开始，单位：度
	double	DetectAng_Yaw_Stop;	// 	方位最大扫描中心角结束，单位：度
	double	DetectRange_Yaw;	// 	方位最大扫描范围，单位：度
	double	DetectAng_Pitch;	// 	俯仰最大扫描中心角，单位：度
	double	DetectRange_Pitch;	// 	俯仰最大扫描范围，单位：度
	short	Fc;					// 	载频 0：C波段(2~4)；1：S波段(4~8)
	double	DetectRangeMax;		// 	参考威力范围，单位：米
	bool	Type_MTI;			// 	使用MTI
	bool	Type_MTD;			// 	使用MTD
};

// 火力车
struct FireCar {
	double lon;		// 	经度
	double lat;		// 	纬度
	double alt;		// 	高度
	double yaw;		// 	方位角
	double pitch;	// 	俯仰角
	double roll;	// 	滚转角
};

// 火力系统
struct FireSys {
	double	Offset_x;				//	相对于火力车的偏移x，单位：米
	double	Offset_y;				//	相对于火力车的偏移y，单位：米
	double	Offset_z;				//	相对于火力车的偏移z，单位：米
	short	Caliber_Gun;			//	火炮口径，单位：毫米
	short	Number_GunBarrel;		//	身管数
	short	Type_Carrier;			//	载体类型 0：自行履带；1：自行轮式；2：牵引
	short	Method_Launching;		//	发射方式 0：并行；1：串行；2：转管；3：转膛
	double	PitchAng_Gun;			//	火炮射界高低角中心线 单位：度
	double	PitchRange_Gun;			//	火炮射界高低角范围 单位：度
	double	DisRange_Gun;			//	火炮火力范围 单位：米
	double	Speed_Shoot_Gun;		//	射速 单位：发/min	
	short	Methods_ShootLen;		//	射击长度 0：单发；1：短点射；2：长点射；3：连射
	short	ShellNum_NoShooting;	//	火炮弹量 单位：发
	short	Type_Shell;				//	火炮弹种 0：杀爆弹；1：脱壳穿甲弹；2：预置破片弹
	double	InitialSpeed_Shell;		//	弹丸初速 单位：米/秒
	double	DisRange_Mis;			//	导弹火力范围 单位：米
	short	Num_Mis;				//	导弹装弹数
	double	VerOffsetAng_Mis;		//	导弹最大离轴方位角 单位：度
	double	HorOffsetAng_Mis;		//	导弹俯仰角覆盖中心线 单位：度
	double	HorOffsetAngRange_Mis;	//	导弹俯仰角覆盖范围 单位：度
};

// 搜索雷达
struct TearchRadar {
	double	Offset_x;			//	相对于指挥车的偏移x，单位：米
	double	Offset_y;			//	相对于指挥车的偏移y，单位：米
	double	Offset_z;			//	相对于指挥车的偏移z，单位：米
	short	DetectCycle;		//	扫描周期，单位：秒
	short	RadarType;			//	雷达体制 0：机械；1：一维相控阵；2：二维相控阵
	double	DetectAng_Yaw_Start;//	方位最大扫描中心角开始，单位：度
	double	DetectAng_Yaw_Stop;	//	方位最大扫描中心角结束，单位：度
	double	DetectRange_Yaw;	//	方位最大扫描范围，单位：度
	double	DetectAng_Pitch;	//	俯仰最大扫描中心角，单位：度
	double	DetectRange_Pitch;	//	俯仰最大扫描范围，单位：度
	short	Fc;					//	载频 0：C波段(2~4)；1：S波段(4~8)
	double	DetectRangeMax;		//	参考威力范围，单位：米
	bool	Type_MTI;			//	使用MTI
	bool	Type_MTD;			//	使用MTD
};

// 跟踪雷达
struct TrackRadar{
	double	Offset_x;			//	相对于指挥车的偏移x，单位：米
	double	Offset_y;			//	相对于指挥车的偏移y，单位：米
	double	Offset_z;			//	相对于指挥车的偏移z，单位：米
	short	RadarType;			//	雷达体制 0：机械；1：一维相控阵；2：二维相控阵
	double	DetectAng_Yaw_Start;//	方位最大扫描中心角开始，单位：度
	double	DetectAng_Yaw_Stop;	//	方位最大扫描中心角结束，单位：度
	double	DetectRange_Yaw;	//	方位最大扫描范围，单位：度
	double	DetectAng_Pitch;	//	俯仰最大扫描中心角，单位：度
	double	DetectRange_Pitch;	//	俯仰最大扫描范围，单位：度
	short	Fc;					//	载频 0：Ka波段
	double	DetectRangeMax;		//	参考威力范围，单位：米
	bool	Type_MTI;			//	使用MTI
	bool	Type_MTD;			//	使用MTD
	double	Turn_Az_Vel;		//	方位转动角速度，单位：度/秒
	double	Turn_El_Vel;		//	俯仰转动角速度，单位：度/秒
	double	Turn_Az_Acc;		//	方位转动角加速度，单位：度/秒平方
	double	Turn_El_Acc;		//	俯仰转动角加速度，单位：度/秒平方
	double	Turn_Az_Error;		//	方位伺服跟踪精度，单位：度
	double	Turn_El_Error;		//	俯仰伺服跟踪精度，单位：度
};

// 光电跟踪
struct PhotTrack{
	double	Offset_x;					//	相对于指挥车的偏移x，单位：米
	double	Offset_y;					//	相对于指挥车的偏移y，单位：米
	double	Offset_z;					//	相对于指挥车的偏移z，单位：米
	double	DetectAng_Yaw_Start;		//	方位最大扫描中心角开始，单位：度
	double	DetectAng_Yaw_Stop;			//	方位最大扫描中心角结束，单位：度
	double	DetectAngRange_Yaw;			//	方位最大扫描范围，单位：度
	double	DetectAng_Pitch;			//	俯仰最大扫描中心角，单位：度
	double	DetectAngRange_Pitch;		//	俯仰最大扫描范围，单位：度
	double	DetectAngSpeedMax_Pitch;	//	最大跟踪高低角速度，单位：度/秒
	double	DetectAngAccMax_Pitch;		//	最大跟踪高低角加速度，单位：度/秒平方
	double	DetectAngSpeedMax_Yaw;		//	最大跟踪方位角速度，单位：度/秒
	double	DetectAngAccMax_Yaw;		//	最大跟踪方位角加速度，单位：度/秒平方
	double	DetectRangeMax;				//	威力范围，单位：米
	double	ServoPre;					//	伺服跟踪精度，单位：度
	bool	LaserWork;					//	激光测距
	double	LaserDisPre;				//	激光测距精度，单位：米
};

// 固定翼飞机
struct FixedWing{
	double lon;				//	经度
	double lat;				//	纬度
	double alt;				//	高度
	double yaw;				//	方位角
	double pitch;			//	俯仰角
	double roll;			//	滚转角
	int jumpToPoint;		//	路径编号
	double RCS;				//	RCS, 单位：平方米
	short RCS_Type;			//	RCS起伏类型, 0-swerling0, 1-swerling1, 2-swerling2, 3-swerling3, 4-swerling4
	double Length;			//	机长, 单位：米
	double Width;			//	翼展, 单位：米
	double Height;			//	机高, 单位：米
	bool InterfereFlag;		//	有源压制干扰, 0-无， 1-有
	double carrierFrequency;//载频, 单位：兆赫兹
	double bandwidth;		//带宽, 单位：兆赫兹
	double power;			//功率, 单位：分贝毫瓦
};

// 直升机
struct Helicopter{
	double lon;				//	经度
	double lat;				//	纬度
	double alt;				//	高度
	double yaw;				//	方位角
	double pitch;			//	俯仰角
	double roll;			//	滚转角
	int jumpToPoint;		//	路径编号
	double RCS;				//	RCS, 单位：平方米
	short RCS_Type;			//	RCS起伏类型, 0-swerling0, 1-swerling1, 2-swerling2, 3-swerling3, 4-swerling4
	double Length;			//	机长, 单位：米
	double Width;			//	翼展, 单位：米
	double Height;			//	机高, 单位：米
	bool InterfereFlag;		//	有源压制干扰, 0-无， 1-有
	double carrierFrequency;//载频, 单位：兆赫兹
	double bandwidth;		//带宽, 单位：兆赫兹
	double power;			//功率, 单位：分贝毫瓦
};

// 无人机
struct UAV{
	double lon;				//	经度
	double lat;				//	纬度
	double alt;				//	高度
	double yaw;				//	方位角
	double pitch;			//	俯仰角
	double roll;			//	滚转角
	int jumpToPoint;		//	路径编号
	double RCS;				//	RCS, 单位：平方米
	short RCS_Type;			//	RCS起伏类型, 0-swerling0, 1-swerling1, 2-swerling2, 3-swerling3, 4-swerling4
	double Length;			//	机长, 单位：米
	double Width;			//	翼展, 单位：米
	double Height;			//	机高, 单位：米
	bool InterfereFlag;		//	有源压制干扰, 0-无， 1-有
	double carrierFrequency;//载频, 单位：兆赫兹
	double bandwidth;		//带宽, 单位：兆赫兹
	double power;			//功率, 单位：分贝毫瓦
};

// 巡航导弹
struct CruiseMissile{
	double lon;				//	经度
	double lat;				//	纬度
	double alt;				//	高度
	double yaw;				//	方位角
	double pitch;			//	俯仰角
	double roll;			//	滚转角
	int jumpToPoint;		//	路径编号
	double RCS;				//	RCS, 单位：平方米
	short RCS_Type;			//	RCS起伏类型, 0-swerling0, 1-swerling1, 2-swerling2, 3-swerling3, 4-swerling4
	double Length;			//	机长, 单位：米
	double Width;			//	翼展, 单位：米
	double Height;			//	机高, 单位：米
};

// 精确制导炸弹
struct GuidedBomb{
	double lon;				//	经度
	double lat;				//	纬度
	double alt;				//	高度
	double yaw;				//	方位角
	double pitch;			//	俯仰角
	double roll;			//	滚转角
	int jumpToPoint;		//	路径编号
	double RCS;				//	RCS, 单位：平方米
	short RCS_Type;			//	RCS起伏类型, 0-swerling0, 1-swerling1, 2-swerling2, 3-swerling3, 4-swerling4
	double Length;			//	机长, 单位：米
	double Width;			//	翼展, 单位：米
	double Height;			//	机高, 单位：米
};

*/