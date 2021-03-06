//
//  ADClient.h
//  iAd
//
//  Copyright 2013 Apple, Inc. All rights reserved.
//
//

#import <Foundation/Foundation.h>

NS_CLASS_AVAILABLE_IOS(7_1) @interface ADClient : NSObject

/*!
 * @method sharedClient
 *
 * @return
 * The shared singleton instance of ADClient.
 *
 * @discussion
 * ADClient is a singleton object.
 */
+ (ADClient *)sharedClient NS_AVAILABLE_IOS(7_1);

/*!
 * @method determineAppInstallationAttributionWithCompletionHandler:
 *
 * @param completionHandler
 * A block accepting one BOOL argument that will be called when app installation
 * attribution status has been determined. If this installation of the app is
 * attributed to an iAd impression, the completion handler will be called with
 * YES. Otherwise, or if the user has enabled Limit Ad Tracking, the completion
 * handler will be called with NO.
 *
 * The handler will be called on an arbitrary queue.
 *
 * @discussion
 * Provides a way for an app to determine if it was installed by the user in
 * response to seeing an iAd for the app.
 */
- (void)determineAppInstallationAttributionWithCompletionHandler:(void (^)(BOOL appInstallationWasAttributedToiAd))completionHandler NS_AVAILABLE_IOS(7_1);

/*!
 * @method lookupAdConversionDetails:
 *
 * @param completionHandler
 * A block which will be called with the app purchase date and the date at which
 * the user saw an iAd for the app. If no conversion has been tracked, or if
 * Limit Ad Tracking is enabled on the device, both dates will be nil.
 *
 * The handler will be called on an arbitrary queue.
 *
 * @discussion
 * Provides a way for an app to determine when an iAd was shown to the user
 * which resulted in the user's purchase of the app.
 */
- (void)lookupAdConversionDetails:(void (^)(NSDate *appPurchaseDate, NSDate *iAdImpressionDate))completionHandler NS_AVAILABLE_IOS(8_0);

/*!
 * @method addClientToSegments:replaceExisting:
 *
 * @param segmentIdentifiers
 * Array of NSString objects identifying which segments to add the client to.
 * May be nil.
 *
 * @param replaceExisting
 * If YES, the client will be removed from all existing segments prior to
 * being added to the specified segments.
 *
 * @discussion
 * Enables apps to add users to custom segments owned and defined by the calling
 * application.  If Limit Ad Tracking is enabled on the device, this method will
 * have no effect.
 */
- (void)addClientToSegments:(NSArray *)segmentIdentifiers replaceExisting:(BOOL)replaceExisting NS_AVAILABLE_IOS(8_0);

@end
