//
//  Baiduface.m
//  HelloCordova
//
//  Created by Embrace on 2018/6/15.
//

#import "Baiduface.h"

@implementation Baiduface

//调用百度人脸识别接口
- (void)getFaceImage:(CDVInvokedUrlCommand *)command {
    __weak typeof(self) weakSelf = self;
    NSDictionary *options = [command.arguments objectAtIndex:0];
    self.hasPendingOperation = YES;
    self.latestCommand = command;
    
    if ([[FaceSDKManager sharedInstance] canWork]) {
        NSString* licensePath = [[NSBundle mainBundle] pathForResource:FACE_LICENSE_NAME ofType:FACE_LICENSE_SUFFIX];
        [[FaceSDKManager sharedInstance] setLicenseID:FACE_LICENSE_ID andLocalLicenceFile:licensePath];
    }

    weakSelf.detectionVC = [[DetectionViewController alloc] init];
    UINavigationController *navi = [[UINavigationController alloc] initWithRootViewController:weakSelf.detectionVC];
    navi.navigationBarHidden = true;
    
    [weakSelf.detectionVC setDidFinishGetFaceImageHandle:^(UIImage *faceImage) {
        
        dispatch_async(dispatch_get_main_queue(), ^{
            NSString *PathString;
            NSString *path = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) lastObject];
            
            // 拼接图片的路径
            NSDateFormatter *formater = [[NSDateFormatter alloc] init];
            
            //用时间给文件全名，以免重复
            [formater setDateFormat:@"yyyyMMddHHmmss"];
            
            PathString = [path stringByAppendingPathComponent:[NSString stringWithFormat:@"%@.jpg",[formater stringFromDate:[NSDate date]]]];
            
            [UIImageJPEGRepresentation(faceImage,0.5) writeToFile:PathString atomically:YES];
//            self.ImagView.image =faceImage;
            NSLog(@"PathString is +== %@",PathString);
            
            [self getImagePath:PathString];
            
        });
    }];
    
    [self.viewController presentViewController:navi animated:YES completion:nil];
}

//将取到的人脸照片传到ionic项目中
- (void)getImagePath:(NSString *)imagePath {
    NSDictionary *upLoadDic;
    upLoadDic = [NSDictionary dictionaryWithObjectsAndKeys:imagePath,@"picture", nil];
    CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:upLoadDic];
    [self.commandDelegate sendPluginResult:result callbackId:self.latestCommand.callbackId];
}

@end
