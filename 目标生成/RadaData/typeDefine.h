#pragma once
#pragma pack(1)
// 报文头
struct MessageHeader {
	char	dataType;		        // 数据类型(1)
	short	nodeID;		            // 节点ID
	int		sourceID;		        // 发送方ID(3)
	char	childDataType;			// 数据类型(2)
	int		dataLen;		        // 数据正文字节长度
	int		serialNumber;	        // 报文流水号
	double	time;			        // 时间戳
	char	version;		        // 版本号
};
//***************************************************************************************************//
// 消息类型（每个数据表前四个字节（int）标识消息类型）
enum EMsgType {
	STATUS = 1,	   // 状态消息(状态数据只用于发送节点心跳，状态数据无正文)
	COMMAND = 2,   // 指令消息
	DATA = 3,	   // 数据消息
};

// 指令（指令类消息的消息内容）
enum ECommandType {
	CommondNone = 0,				// 空指令
	CommondSimStart = 1,			// 仿真开始指令
	CommondSimPause = 2,			// 仿真暂停指令
	CommondSimStop = 3,			    // 仿真结束指令
	CommondSimPlayBack = 4,		    // 仿真回放指令
	CommondSituInit = 5,			// 态势初始化指令
	CommondSituInitReturn = 6,	    // 态势初始化指令回令
	CommondSituBind = 7,			// 态势装订指令
	CommondSituBindOk = 8,			// 态势装订完成指令（态势数据装订完成发送该消息）
	CommondSituBindReturn = 9,	    // 态势装订完成回令
	CommondSaveTestData = 10		// 保存试验数据指令
};

// 数据类型
enum EDataType {
	DataTypeNull = -1,			    // 无效数据类型
	DataTypeTargetTrueValue = 11,	// 目标真值信息
	DataTypeDamageDecide = 12,	    // 目标毁伤裁决信息
	DataTypeArtilleryStatus = 13,	// 火炮状态信息
	DataTypeMissileDynamic = 14,	// 导弹动态信息
	DataTypeTargetFuseGuide = 15,	// 目标融合导引信息
	DataTypeTargetAssign = 16,	    // 目标分配信息
	DataTypeArtilleryStrike = 17,	// 火力打击信息
	DataTypeTargetInRadar = 18,	    // 目指雷达信息
	DataTypeSearchRadar = 19,		// 搜索雷达信息
	DataTypeTrackRadar = 20,		// 跟踪雷达信息
	DataTypePhotElecTrack = 21,	    // 光电跟踪信息
};

// 11--目标真值信息
struct TargetTrueValueInfo{
	short targetId;				// 目标编号
	signed char type;			/* 目标类型：1-固定翼飞机；2-直升机；3-无人机；
								4-巡航导弹；5-精确制导炸弹*/
	double x;					// x方向坐标
	double y;					// y方向坐标
	double z;					// z方向坐标
	double Vx;					// x方向速度
	double Vy;					// y方向速度
	double Vz;					// z方向速度
	double Ax;					// x方向加速度
	double Ay;					// y方向加速度
	double Az;					// z方向加速度
	double yaw;					// 偏航角
	double pitch;				// 俯仰角
	double roll;				// 横滚角
	signed char interfereFlag;	// 有源压制干扰标志位
	double carrierFrequency;	// 载频
	double bandwidth;			// 带宽
	double power;				// 功率
	double rcs;					// RCS
	signed char rcsType;		// RCS起伏
};

// 12--目标毁伤裁决信息
struct TargetDamageVerdictInfo{
	short targetId; 		// 毁伤的目标的编号	
	double damageTime; 		// 损毁时间	
};

// 13--火炮状态信息
struct ArtilleryStatusInfo{
	double gunAzimuth;		    // 炮方位角		
	double gunHeightangle;		// 炮高低角		
	signed char fireStatus;		/* 火炮射击状态：0-空闲，1-导弹发射状态，
								2-炮弹发射状态，3-弹炮结合发射状态，4-准备中*/
	short missileLaunchedNum;	// 导弹发射弹量	
	short missileResidualNum;	// 导弹余弹数		
	short shellLaunchedNum;	    // 炮弹发射弹量	
	short shellResidualNum;	    // 炮弹余弹数		
};

// 14--导弹动态信息
struct MissileDynamicInfo{
	short targetNo;		// 目标批号：目标批号指火力融合后的目标批号
	short targetId;		// 目标编号：目标编号指主控台发出的目标真值的ID号
	int missileId;		        // 导弹编号	
	signed char missileStatus;	// 导弹状态：1-飞行，2-击中目标，3-自毁	
	double x;			// x方向坐标
	double y;			// y方向坐标
	double z;			// z方向坐标
	double Vx;			// x方向速度
	double Vy;			// y方向速度
	double Vz;			// z方向速度
	double yaw;			// 偏航角	
	double pitch;		// 俯仰角	
	double roll;		// 横滚角	
};

// 15--目标融合导引信息
struct TargetFusionInfo{
	short targetNumber; // 目标批数
};
// 目标信息
struct TargetGuideInfo{
	short targetNo;	// 目标批号	
	short targetId;	// 目标编号
	signed char leadFlag;	/* 是否导引信息：0：非目标导引信息；1：目标导引信息-跟踪雷达工作；
							2：目标导引信息-光电跟踪工作；3：目标导引信息-跟踪雷达和光电跟踪都工作*/
	double x;		// x方向坐标		
	double y;		// y方向坐标		
	double z;		// z方向坐标		
	double Vx;		// x方向速度		
	double Vy;		// y方向速度		
	double Vz;		// z方向速度		
	double Ax;		// x方向加速度	
	double Ay;		// y方向加速度	
	double Az;		// z方向加速度	
	double yaw;		// 目标方位角
	double pitch;	// 目标高低角		
};

// 16--目标分配信息
struct TargetAssignmentInfo{
	short fireID;	 			// 火力系统ID		
	signed char targetNumber; 	// 分配的目标的批数	
};
//分配的目标信息
struct AssTargetInfo{
	short targetNo;	 			// 目标批号
	short targetId;				// 目标编号
	short threatLevel; 			// 目标威胁度
	double x;				    // 目标x方向坐标			
	double y;				    // 目标y方向坐标			
	double z;				    // 目标z方向坐标		
	double Vx;				    // 目标x方向速度		
	double Vy;				    // 目标y方向速度		
	double Vz;				    // 目标z方向速度
};	

// 17--火力打击信息（为单次打击结果数据）
struct ArtilleryStrikeInfo{
	short targetNo;		// 目标批号：目标批号指火力融合后的目标批号	
	short targetId;		// 目标编号：目标编号指主控台发出的目标真值的ID号
	signed char projectileType;	    // 弹种类型：1-炮弹；2-导弹
	signed char totalNumber;		// 单次射击的射击发数			
	signed char effectiveNumber;	// 单次射击的命中发数
	double xDirDeviation;	// X方向偏差（统计值）
	double yDirDeviation;	// Y方向偏差（统计值）
	double zDirDeviation;	// Z方向偏差（统计值）
};

// 雷达信息--探测目标信息
struct TargetDetectInfo{
	short targetNo;			    // 目标批号
	short targetId;			    // 目标编号
	double trackTime;		    // 跟踪时间			
	double x;				    // x方向坐标			
	double y;				    // y方向坐标			
	double z;				    // z方向坐标		
	double Vx;				    // x方向速度		
	double Vy;				    // y方向速度		
	double Vz;				    // z方向速度		
	double yaw;				    // 目标方位角		
	double pitch;				// 目标高低角		
	double detectionDistance;	// 目标斜距		
};

// 18--目指雷达信息--基本信息
struct TargetIndRadarInfo{
	double radarAzimuth;		// 雷达方位角		
	double radarHeightangle;	// 雷达高低角		
	signed char radarTrackDim;	// 数据维度：1- 一维数据，俯仰维无效；2- 二维数据，俯仰维有效
	short targetNumber;		    // 目标批数
};

// 19--搜索雷达信息---基本信息
struct SearchRadarInfo{
	double radarAzimuth;		// 雷达方位角		
	double radarHeightangle;	// 雷达高低角		
	signed char radarTrackDim;	// 数据维度：1- 一维数据，俯仰维无效；2- 二维数据，俯仰维有效
	short targetNumber;		    // 目标批数	
};

// 20--跟踪雷达信息 -- 基本信息 
struct TrackRadarInfo{
	double radarAzimuth;		// 雷达方位角		
	double radarHeightangle;	// 雷达高低角		
	signed char radarTrackDim;	// 数据维度：1- 一维数据，俯仰维无效；2- 二维数据，俯仰维有效
};

// 21--光电跟踪信息
struct PhotoelecTrackInfo{
	double photoelecAzimuth;		// 光电方位角		
	double photoelecHeightangle;	// 光电高低角		
	short targetNo;				    // 目标批号
	short targetId;			    	// 目标编号
	signed char trackStatus;		// 跟踪状态：0-未跟踪；1-跟踪良好；2-目标丢失			
	double detectionDistance;		// 目标斜距				
	double azimuthTrackError;		// 方位角跟踪误差			
	double heightangleTrackError;	// 高低角跟踪误差			
};

#pragma pack()