//
//  PROKeyValueObserver.h
//  Proton
//
//  Created by Justin Spahr-Summers on 23.12.11.
//  Copyright (c) 2011 Emerald Lark. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * The type for a KVO callback block.
 *
 * This type of block accepts an `NSDictionary` of changes, matching the
 * structure of the dictionary passed to
 * `observeValueForKeyPath:ofObject:change:context:`.
 */
typedef void (^PROKeyValueObserverBlock)(NSDictionary *);

/**
 * Implements support for key-value observation using blocks.
 *
 * This class is immutable, and conforms to `<NSCopying>` so that instances can
 * be used as keys in a dictionary. Attempting to copy an instance will just
 * return the same object.
 */
@interface PROKeyValueObserver : NSObject <NSCopying>

/**
 * @name Initialization
 */

/**
 * Invokes <initWithTarget:keyPath:options:block:> without any options.
 *
 * Observation will begin immediately, and will not stop until the receiver is
 * destroyed.
 *
 * @param target The object to observe. This object must support weak
 * references being formed to it.
 * @param keyPath The key path, relative to the `target`, to observe for
 * changes.
 * @param block The block to invoke when a change notification is sent.
 *
 * @warning **Important:** Although `target` is saved only as a weak reference,
 * it is still undefined behavior for the receiver to remain alive longer than
 * the target object. The `<NSKeyValueObserving>` protocol specifies that
 * observations must cease before the observed object is deallocated.
 */
- (id)initWithTarget:(id)target keyPath:(NSString *)keyPath block:(PROKeyValueObserverBlock)block;

/**
 * Initializes the receiver to observe the given target and key path, invoking
 * the given block when a change occurs.
 *
 * Observation will begin immediately, and will not stop until the receiver is
 * destroyed.
 *
 * This is the designated initializer.
 *
 * @param target The object to observe. This object must support weak
 * references being formed to it.
 * @param keyPath The key path, relative to the `target`, to observe for
 * changes.
 * @param options A bitmask of options controlling the information that will be
 * provided in the KVO change dictionary.
 * @param block The block to invoke when a change notification is sent.
 *
 * @warning **Important:** Although `target` is saved only as a weak reference,
 * it is still undefined behavior for the receiver to remain alive longer than
 * the target object. The `<NSKeyValueObserving>` protocol specifies that
 * observations must cease before the observed object is deallocated.
 */
- (id)initWithTarget:(id)target keyPath:(NSString *)keyPath options:(NSKeyValueObservingOptions)options block:(PROKeyValueObserverBlock)block;

/**
 * @name Key-Value Observation Properties
 */

/**
 * The object being observed.
 *
 * @warning **Important:** Although this object is saved only as a weak
 * reference, it is still undefined behavior for the receiver to remain alive
 * longer than the target object. The `<NSKeyValueObserving>` protocol specifies
 * that observations must cease before the observed object is deallocated.
 */
@property (nonatomic, weak, readonly) id target;

/**
 * The key path, relative to the <target>, being observed.
 */
@property (nonatomic, copy, readonly) NSString *keyPath;

/**
 * The block that will be invoked when a change occurs.
 */
@property (nonatomic, copy, readonly) PROKeyValueObserverBlock block;

/**
 * The key-value observing options that the receiver was initialized with.
 */
@property (nonatomic, assign, readonly) NSKeyValueObservingOptions options;

@end