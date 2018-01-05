// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2014-2016
//
// - - - - - - - - - - - - - - - - - - - -

#import <Foundation/Foundation.h>

/**
 * DMReaderOptionKey type may be used to define key strings
 * for DMSReader options Dictionaries.
 * <br/><br/>
 */

NS_SWIFT_NAME(ReaderOptionKey)
#if defined(NS_EXTENSIBLE_STRING_ENUM)
NS_SWIFT_NAME(ReaderOptionKey)
///Defines the options that can be used with a reader.
typedef NSString * _Nonnull const DMSReaderOptionKey NS_EXTENSIBLE_STRING_ENUM;
#else
///Defines the options that can be used with a reader.
typedef NSString * _Nonnull const DMSReaderOptionKey;
#endif

NS_SWIFT_NAME(Reader)
///Readers are a family of classes with a synchronous interface for detection, meant for custom or offline/not realtime uses. DMSReader cannot be instantiated directly. Instead use one of the subclasses.
@interface DMSReader : NSObject


/*-------------------------------------------------------------------------------------*/
#pragma mark - Reader Errors
/*-------------------------------------------------------------------------------------*/

NS_SWIFT_NAME(ReaderErrorDomain)
///The domain for any errors returned from a reader
extern NSString * _Nonnull const DMSReaderErrorDomain;

///Error codes that could be returned from DMSDK readers
typedef NS_ENUM(NSInteger, DMSReaderErrorCode)
{
    ///Returned when a sample buffer has been passed to a reader in a format it does not understand.
    DMSReaderErrorCodeUnableToHandleMediaFormat,
    ///This error occurs when a service is unavailable for one or more symbologies. Implies that other symbologies may have been processed sucessfully, but not all. In some cases, if an internet connection is not avaialble but it required for a symbology, the reader may return this error instead of attempting to create a connection to a cloud service. This error is usually returned by the reader result. The userinfo will include the DMSReaderErrorUserInfoKeyAffectedSymbologies, with the value being the bitmask of symbologies unavailable.
    DMSReaderErrorCodeServiceUnavailable
} NS_SWIFT_NAME(ReaderErrorCode);


NS_SWIFT_NAME(ReaderErrorUserInfoKey)
#if defined(NS_EXTENSIBLE_STRING_ENUM)
NS_SWIFT_NAME(ReaderErrorUserInfoKey)
///Defines the keys for userinfo returned by a reader result
typedef NSString * _Nonnull const DMSReaderErrorUserInfoKey NS_EXTENSIBLE_STRING_ENUM;
#else
///Defines the keys for userinfo returned by a reader result
typedef NSString * _Nonnull const DMSReaderErrorUserInfoKey;
#endif

NS_SWIFT_NAME(affectedSymbologies)
///Returns a bitmask representing the symbologies that could not be processed due to the error.
extern DMSReaderErrorUserInfoKey  _Nonnull const DMSReaderErrorAffectedSymbologiesUserInfoKey;

@end
