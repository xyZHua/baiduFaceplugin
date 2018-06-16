//
//  Baiduface.h
//  HelloCordova
//
//  Created by Embrace on 2018/6/15.
//

#import <Foundation/Foundation.h>
#import <Cordova/CDVPlugin.h>
#import "DetectionViewController.h"
#import "IDLFaceSDK/IDLFaceSDK.h"
#import "FaceParameterConfig.h"


@interface Baiduface : CDVPlugin

@property (strong, nonatomic) CDVInvokedUrlCommand* latestCommand;
@property (readwrite, assign) BOOL hasPendingOperation;
@property (nonatomic, strong) DetectionViewController *detectionVC;

- (void)getFaceImage:(CDVInvokedUrlCommand *)command;
- (void)getImagePath:(NSString *)imagePath;

@end
