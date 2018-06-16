//
//  FaceSDK.h
//  FaceSDK
//
//  Created by Nick(xuli02) on 15/3/31.
//  Copyright (c) 2015年 Baidu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

typedef enum
{
    FaceSDKImgTypeYUV,
    FaceSDKImgTypeRGB,
}FaceSDKImageType;

typedef enum
{
    FaceSDKMethodTypeSDM = 0,
    FaceSDKMethodTypeCDNN = 1,
    FaceSDKMethodTypeSDM_7PTS = 2,
    FaceSDKMethodTypeSDM_15PTS = 3,
}FaceSDKMethodType;

typedef enum
{
    FaceSDKDetectMethodType_BOOST,
    FaceSDKDetectMethodType_CNN
}FaceSDKDetectMethodType;

typedef enum
{
    FaceSDKParsingModelType_NOT_USE = 0,
    FaceSDKParsingModelType_CLASS_NUM_3 = 1,
    FaceSDKParsingModelType_CLASS_NUM_7 = 2,
    FaceSDKParsingModelType_CLASS_NUM_10 = 3,
} FaceSDKParsingModelType;

typedef enum
{
    QualitySDKModelType_NOT_USE,
    QualitySDKModelType_BLUR,
    QualitySDKModelType_OCCLUSION,
} QualitySDKModelType;

typedef enum
{
    LicenseSuccess = 0,
    LicenseInitError,
    LicenseDecryptError,
    LicenseInfoFormatError,
    LicenseExpired,
    LicenseMissRequiredInfo,
    LicenseInfoCheckError,
    LicenseLocalFileError,
    LicenseRemoteDataError
} FaceLicenseErrorCode;


//typedef enum
//{
//    QualitySDKModelType_NOT_USE = 0,
//    QualitySDKModelType_BLUR = 1,
//    QualitySDKModelType_OCCLUSION = 2,
//} QualitySDKModelType;

NS_ASSUME_NONNULL_BEGIN
@interface LivenessState : NSObject

@property (nonatomic, assign) BOOL isLiveEye;
@property (nonatomic, assign) NSInteger leftEyeStatus;
@property (nonatomic, assign) NSInteger rightEyeStatus;

@property (nonatomic, assign) BOOL isLiveMouth;
@property (nonatomic, assign) NSInteger mouthStatus;

@property (nonatomic, assign) BOOL isLiveYawLeft;
@property (nonatomic, assign) BOOL isLiveYawRight;
@property (nonatomic, assign) NSInteger yawAngles;

@property (nonatomic, assign) BOOL isLivePitchUp;
@property (nonatomic, assign) BOOL isLivePitchDown;
@property (nonatomic, assign) NSInteger pitchAngles;

@end

@interface FaceSDK : NSObject

//Please use this method to get an instance
+ ( FaceSDK * _Nullable )sharedInstance;


/**
 *  init with authorization api key,this method should be called before any other instance methods
 *
 *
 *  @param apiKey: authorized api key
 *
 *  @param localLicencePath localLicensePath
 */

- (void)initWithLicenseID:(NSString *)licenseId andLocalLicenceFile:(NSString *)localLicencePath;

- (void)initWithToken:(NSString *)token;

/**
 *  Check Available
 *
 *  @return if SDK APIs  Available
 */
- (FaceLicenseErrorCode)canWork;

/**
 *  Detect
 *
 *  @param image      input image
 *  @param methodType input detection method type:SDM / CDNN
 *  @param minSize    input specify minimum size of faces to be detected
 *  @param faceRects  output positions of faces detected,described with CGRect struct stored in NSValue
 *  @param faceNumber output number of faces detected
 */
- (void)detectFaceInImage:(UIImage *)image
           withMethodType:(FaceSDKMethodType)methodType
          andGetFaceRects:( NSArray *_Nullable*_Nullable)faceRects
            andFaceNumber:(NSInteger *)faceNumber
       andMinimumFaceSize:(NSInteger)minSize;

/**
 *  Align
 *
 *  @param image         input image
 *  @param methodType    input detection Method Type:SDM / CDNN
 *  @param faceRect      input location of face to be aligned
 *  @param faceShape     output faceShape description with CGPoint Value
 *  @param numberOfPoint output number of Points whitch discribe face shape
 *  @param score         output confidence score
 */

- (void)alignFaceInImage:(UIImage *)image
          withMethodType:(FaceSDKMethodType)methodType
             andFaceRect:(CGRect)faceRect
      andOutputFaceShape:( NSArray *_Nullable*_Nullable)faceShape
           andNumOfPoints:(NSInteger *)numberOfPoint
                andScore:(CGFloat *)score;

/**
 *  Align
 *
 *  @param image         input image
 *  @param methodType    input detection Method Type:SDM / CDNN
 *  @param faceShape     input and output faceShape description with CGPoint Value
 *  @param numberOfPoint input number of Points whitch discribe face shape
 */
- (void)fineAlignFaceInImage:(UIImage *)image
              withMethodType:(FaceSDKMethodType)methodType
                andFaceShape:( NSArray *_Nullable*_Nullable)faceShape
              andNumOfPoints:(NSInteger)numberOfPoints;

/**
 *  Track
 *
 *  @param image         input image
 *  @param methodType    input detection Method Type:SDM / CDNN
 *  @param faceShape     input and output faceShape description with CGPoint Value
 *  @param numberOfPoint input number of Points whitch discribe face shape
 *  @param score         output value as confidence score
 */
- (void)trackFaceInImage:(UIImage *)image
          withMethodType:(FaceSDKMethodType)methodType
            andFaceShape:( NSArray *_Nullable*_Nullable)faceShape
          andNumOfPoints:(NSInteger )numberOfPoints
                andScore:(CGFloat *)score;

/**
 *  Parsing
 *
 *  @param image         input image
 *  @param modelType     input parsing model type:outline / detail features
 *  @param faceShape     input faceShape description with CGPoint Value
 *  @param numberOfPoint input number of Points whitch discribe face shape
 *
 *  @return
 */
- (unsigned char *)parsingFaceInImage:(UIImage *)image
                 withParsingModelType:(FaceSDKParsingModelType)modelType
                         andFaceShape:(NSArray *)faceShape
                       andNumOfPoints:(NSInteger )numberOfPoints;

/**
 *  HeadPost Estimate(1)
 *
 *  @param faceShape     input and output faceShape description with CGPoint Value
 *  @param numberOfPoint input number of Points whitch discribe face shape
 *  @param rows          input row count of imagedata
 *  @param colums        input colum count of imagedata
 *
 *  @return head post data: pitch,yaw,roll
 */

- (NSDictionary *)headPostEstimationWithFaceShape:(NSArray *)faceShape
                                 andImgDataRowNum:(NSInteger)rows
                                   andImgColumNum:(NSInteger)colums
                                   andNumOfPoints:(NSInteger )numberOfPoints;

/**
 *  HeadPost Estimate(2)
 *
 *  @param image         input image
 *  @param faceShape     input and output faceShape description with CGPoint Value
 *  @param numberOfPoint input number of Points whitch discribe face shape
 *  @param headPose      output 3 values as headpost description
 *  
 *  @return head post data: pitch,yaw,roll
 */
- (NSDictionary *)headPostEstimationWithImage:(UIImage *)image
                                 andFaceShape:(NSArray *)faceShape
                               andNumOfPoints:(NSInteger )numberOfPoints;



/**
 *  LivenessDetect
 *
 *  @param image         input image
 *  @param faceShape     input and output faceShape description with CGPoint Value
 *  @param numberOfPoint input number of Points whitch discribe face shape
 *  @param resetFlag     0:reset(use when traking failed) 1:normal
 *  @param state         output liveness state
 */

- (void)livenessDetectInImage:(UIImage *)image
                 andFaceShape:( NSArray *_Nullable*_Nullable)faceShape
               andNumOfPoints:(NSInteger )numberOfPoints
                      andFlag:(NSInteger)flag
               andOutPutState:(LivenessState *)state;


//~*~*~*~*~*~*~*~*~*~**~**~*~**~*~**~**~**~**~~*~*~*~*~*~*~*~*~*~**~**~*~**~*~**~**~**~**~
#pragma mark - Utils

/**
 *  Get Detail Face Structure from faceShpe Info(目前仅适用于72个特征点的模型)
 *
 *  @param faceShape input faceShape description with CGPoint Value
 *
 *  @return Detail FaceSture:

 *  {0,1,2,3,4,5,6,7,8,9,10,11,12};         //contour
 *  {13,14,15,16,17,18,19,20,13,21};        //left eye
 *  {22,23,24,25,26,27,28,29,22};           //left eye brow
 *  {30,31,32,33,34,35,36,37,30,38};        //right eye
 *  {39,40,41,42,43,44,45,46,39};           //right eye brow
 *  {47,48,49,50,51,52,53,54,55,56,47};     //nose
 *  {51,57,52}; //nose tip
 *  {58,59,60,61,62,63,64,65,58};           //lips outer contour
 *  {58,66,67,68,62,69,70,71,58};           //lips inner contour
 *
 */
- (NSDictionary *)faceDetailFromFaceShapeArray:(NSArray *)faceShape;

@end



#pragma mark -
#pragma mark FaceVerifier

typedef enum {
    FaceVerifierActionTypeDelete = 0,
    FaceVerifierActionTypeRegister,
    FaceVerifierActionTypeVerify,
    FaceVerifierActionTypeRecognition,
    FaceVerifierActionTypeCheckName,
}FaceVerifierActionType;

typedef enum
{
    ErrorCodeOK,
    ErrorCodePitchOutofDownRange,   //头部偏低
    ErrorCodePitchOutofUpRange,   //头部偏高
    ErrorCodeYawOutofLeftRange,     ////头部偏左
    ErrorCodeYawOutofRightRange,     //头部偏右
    ErrorCodePoorIllumination,      //光照不足
    ErrorCodeNoFaceDetected,    //没有检测到人脸
    ErrorCodeDataNotReady,      //数据没有准备好
    ErrorCodeDataHitOne,    //采集到一张图片
    ErrorCodeDataHitLast,   //采集完最后一张
    ErrorCodeImgBlured,     //图像模糊
    ErrorCodeOcclusionLeftEye,  //左眼有遮挡
    ErrorCodeOcclusionRightEye, //右眼有遮挡
    ErrorCodeOcclusionNose,     //鼻子有遮挡
    ErrorCodeOcclusionMouth,    //嘴巴有遮挡
    ErrorCodeOcclusionLeftContour,  //左脸颊有遮挡
    ErrorCodeOcclusionRightContour, //右脸颊有遮挡
    ErrorCodeOcclusionChinCoutour,  //下颚有遮挡
    ErrorCodeFaceNotComplete,   //没有完成
    ErrorCodeUnknowType
}FaceVerifierErrorCode;

@interface FaceVerifier : NSObject

+ ( FaceVerifier * _Nullable )sharedInstance;

/**
 *  set authorization api key,this method should be called before any other instance methods
 *
 *
 *  @param apiKey: authorized api key
 *
 *  @param localLicencePath localLicensePath
 */
- (void)setLicenseID:(NSString *)licenseId andLocalLicenceFile:(NSString *)localLicencePath;

- (void)initWithToken:(NSString *)token;

/**
 *  Check Available
 *
 *  @return if SDK APIs  Available
 */

- (FaceLicenseErrorCode)canWork;

- (void)setMinFaceSize:(NSInteger)size;

- (void)setIfNeedFineAlign:(BOOL)isFineAlign;

//是否返回活体检测结果
- (void)setIsVerifyLive:(BOOL)isVerifyLife;

//每隔多少毫秒做一次质量检测
//- (void)setSampleInterval:(NSTimeInterval)interval;

- (void)setTrackByDetectionInterval:(NSTimeInterval)interval;

- (void)setDetectInVideoInterval:(NSTimeInterval)interval;

- (void)setCropFaceSizeWithWidth:(CGFloat)width;

- (void)setNotFaceThr:(CGFloat)thr;

- (void)setOccluThr:(CGFloat)thr;

- (void)setIllumThr:(NSInteger)thr;

- (void)setBlurThr:(CGFloat)thr;

- (void)setAlignMethodType:(NSInteger)type;

- (void)setEulurAngleThrPitch:(NSInteger)degree yaw:(NSInteger)yawDegree roll:(NSInteger)rollDegree;

//设定一张人脸抠图张数
- (void)setMaxRegImgNum:(NSInteger)imageNum;

-(void)setIsCheckQuality:(BOOL)flag;

- (void)setCropFaceEnlargeRatio:(CGFloat)thr;

- (NSInteger)getCropFaceSize;

/**
 *  getTrackedFace
 *
 *  @return TrackedFaceInfoModel list
 
 *  TrackedFaceInfoModel: faceRect, faceId, landMarks, score, headpose, isLive, regImage, regLandmarks, imgDigest, isDetect, angle, conf
 */
- (NSArray *)getTrackedFace;

- (NSArray *)regImages;

//if under tracking
- (BOOL)isUnderTrack;

//tracking faceshapes
- (NSArray *)faceShapes;

- (void)clearTrackedFaces;


//活体检测状态,仅对单人模式有效(maxfacecount = 1)
- (LivenessState *)livenessState;

//注册用的HttpString仅对单人模式有效(maxfacecount = 1)
//prepared http data string
- (NSString *)httpString;

// errorcode for the process of preparing data
- (NSInteger)errorCode;

/**
 *  Track
 *
 *  @param image         input image
 *  @param count         intput the maximum faces to track
 */
- (void)trackWithImage:(UIImage *)image andMaxFaceCount:(NSUInteger)count;

/**
 *  prepareData
 *
 *  @param image         input image
 *  @param actionType     FaceVerifierActionType
 *  
 *  return FaceVerifierErrorCode
 */
- (FaceVerifierErrorCode)prepareDataWithImage:(UIImage *)image
               andActionType:(FaceVerifierActionType)actionType;

/**
 *  prepareDataForMaxFace
 *
 *  @param image         input image
 *  @param actionType     FaceVerifierActionType
 *
 *  return FaceVerifierErrorCode
 */
- (FaceVerifierErrorCode)prepareDataForMaxFaceWithImage:(UIImage *)image
                                          andActionType:(FaceVerifierActionType)actionType;

/**
 *  imageQuality
 *
 *  @param image         input image
 *  @param faceShape     input faceShape description with CGPoint Value
 *  @param numberOfPoint input number of Points whitch discribe face shape
 *  @param bluriness     output bluriness
 *  @param illum         output illum
 *  @param occlusion     output occllusion part value
 *  @param nOcclupart    output the count of occlusion part
 */
- (void)imageQualityWith:(UIImage *)image
            andFaceShape:( NSArray *_Nullable*_Nullable)faceShape
          andNumOfPoints:(NSInteger )numberOfPoints
               bluriness:(CGFloat *)bluriness
                   illum:(NSInteger *)illum
               occlusion:( NSArray *_Nullable*_Nullable)occlusion
              nOccluPart:(NSInteger *)nOccluPart;

/**
 *  cropFaceImage
 *
 *  @param image         input image
 *  @param faceShape     input faceShape description with CGPoint Value
 *  @param numberOfPoint input number of Points whitch discribe face shape
 *  @param width     output bluriness
 *  @param height         output illum
 *  @param cropImage     output occllusion part value
 *  @param cropShaps    output the count of occlusion part
 */
- (void)cropFaceImageWith:(UIImage *)image
                FaceShape:( NSArray *_Nullable*_Nullable)faceShape
              numOfPoints:(NSInteger )numberOfPoints
           faceImageWidth:(NSInteger)width
          faceImageHeight:(NSInteger)height
                cropImage:(UIImage *_Nullable*_Nullable)cropImage
                cropShaps:(NSArray *_Nullable*_Nullable)cropShaps;

-(void)setLogVisible:(BOOL)visible;

-(NSString *)getVersion;

@end

@interface TrackedFaceInfoModel : NSObject

@property (nonatomic, assign) CGRect faceRect;
@property (nonatomic, assign) NSInteger faceId;
@property (nonatomic, copy) NSArray * landMarks;
@property (nonatomic, assign) CGFloat score;
@property (nonatomic, copy) NSArray * headPose;
@property (nonatomic, copy) NSArray * isLive;
@property (nonatomic, copy) NSArray * regImage;
@property (nonatomic, copy) NSArray * regLandmarks;
@property (nonatomic, copy) NSArray * imgDigest;
@property (nonatomic, assign) BOOL isDetect;
@property (nonatomic, assign) NSInteger angle;
@property (nonatomic, assign) CGFloat conf;

@end

NS_ASSUME_NONNULL_END

