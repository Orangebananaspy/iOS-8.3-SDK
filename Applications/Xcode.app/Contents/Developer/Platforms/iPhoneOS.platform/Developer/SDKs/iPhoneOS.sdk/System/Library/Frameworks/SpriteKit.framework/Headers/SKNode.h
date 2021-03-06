/**
 @header
 
 
 Nodes are the base scene graph nodes used in the SpriteKit scene graph.
 

 @copyright 2011 Apple, Inc. All rights reserve.

*/

#import <SpriteKit/SpriteKitBase.h>

@class SKView, SKAction, SKScene, SKTexture, SKPhysicsBody, SKFieldNode, SKReachConstraints, SKConstraint;

/**
 Blend modes that the SKNode uses to compose with the framebuffer to produce blended colors.
 */
typedef NS_ENUM(NSInteger, SKBlendMode) {
    SKBlendModeAlpha        = 0,    // Blends the source and destination colors by multiplying the source alpha value.
    SKBlendModeAdd          = 1,    // Blends the source and destination colors by adding them up.
    SKBlendModeSubtract     = 2,    // Blends the source and destination colors by subtracting the source from the destination.
    SKBlendModeMultiply     = 3,    // Blends the source and destination colors by multiplying them.
    SKBlendModeMultiplyX2   = 4,    // Blends the source and destination colors by multiplying them and doubling the result.
    SKBlendModeScreen       = 5,    // FIXME: Description needed
    SKBlendModeReplace      = 6     // Replaces the destination with the source (ignores alpha).
} NS_ENUM_AVAILABLE(10_9, 7_0);

/**
 A SpriteKit scene graph node. These are the branch nodes that together with geometric leaf nodes make up the directed acyclic graph that is the SpriteKit scene graph tree.
 
 All nodes have one and exactly one parent unless they are the root node of a graph tree. Leaf nodes have no children and contain some sort of sharable data that guarantee the DAG condition.
 */
#if TARGET_OS_IPHONE
SK_EXPORT @interface SKNode : UIResponder <NSCopying, NSCoding>
#else
SK_EXPORT @interface SKNode : NSResponder <NSCopying, NSCoding>
#endif

- (instancetype)init NS_DESIGNATED_INITIALIZER;

/**
 Support coding and decoding via NSKeyedArchiver.
 */
- (instancetype)initWithCoder:(NSCoder *)aDecoder NS_DESIGNATED_INITIALIZER;

+ (instancetype)node;

+ (instancetype)nodeWithFileNamed:(NSString*)filename;

@property (nonatomic, readonly) CGRect frame;

/**
 Calculates the bounding box including all child nodes in parents coordinate system.
 */
- (CGRect)calculateAccumulatedFrame;

/**
 The position of the node in the parent's coordinate system
 */
@property (nonatomic) CGPoint position;

/**
 The z-order of the node (used for ordering). Negative z is "into" the screen, Positive z is "out" of the screen. A greater zPosition will sort in front of a lesser zPosition.
 */
@property (nonatomic) CGFloat zPosition;

/**
 The Euler rotation about the z axis (in radians)
 */
@property (nonatomic) CGFloat zRotation;

/**
 The scaling in the X axis
 */
@property (nonatomic) CGFloat xScale;
/**
 The scaling in the Y axis
 */
@property (nonatomic) CGFloat yScale;

/**
 The speed multiplier applied to all actions run on this node. Inherited by its children.
 */
@property (nonatomic) CGFloat speed;

/**
 Alpha of this node (multiplied by the output color to give the final result)
 */
@property (nonatomic) CGFloat alpha;

/**
 Controls whether or not the node's actions is updated or paused.
 */
@property (nonatomic, getter = isPaused) BOOL paused;

/**
 Controls whether or not the node and its children are rendered.
 */
@property (nonatomic, getter = isHidden) BOOL hidden;

/**
 Controls whether or not the node receives touch events
 */
@property (nonatomic, getter=isUserInteractionEnabled) BOOL userInteractionEnabled;

/**
 The parent of the node.
 
 If this is nil the node has not been added to another group and is thus the root node of its own graph.
 */
@property (nonatomic, readonly) SKNode *parent;


/**
 The children of this node.
 
 */
@property (nonatomic, readonly) NSArray *children;


/**
 The client assignable name.
 
 In general, this should be unique among peers in the scene graph.
 */
@property (nonatomic, copy) NSString *name;

/**
 The scene that the node is currently in.
 */
@property (nonatomic, readonly) SKScene* scene;

/**
 Physics body attached to the node, with synchronized scale, rotation, and position
 */
@property (nonatomic, retain) SKPhysicsBody *physicsBody;

/**
 An optional dictionary that can be used to store your own data in a node. Defaults to nil.
 */
@property (nonatomic, retain) NSMutableDictionary *userData;

/**
 Kinematic constraints, used in IK solving
 */
@property (nonatomic, copy) SKReachConstraints *reachConstraints;


/**
 Optional array of SKConstraints
 Constraints are evaluated each frame after actions and physics.
 The node's transform will be changed to satisfy the constraint.
 */
@property (nonatomic, copy) NSArray *constraints;

/**
 Sets both the x & y scale
 
 @param scale the uniform scale to set.
 */
- (void)setScale:(CGFloat)scale;

/**
 Adds a node as a child node of this node
 
 The added node must not have a parent.
 
 @param node the child node to add.
 */
- (void)addChild:(SKNode *)node;

- (void)insertChild:(SKNode *)node atIndex:(NSInteger)index;

- (void)removeChildrenInArray:(NSArray *)nodes;
- (void)removeAllChildren;

- (void)removeFromParent;

- (SKNode *)childNodeWithName:(NSString *)name;
- (void)enumerateChildNodesWithName:(NSString *)name usingBlock:(void (^)(SKNode *node, BOOL *stop))block;

/**
 * Simplified shorthand for enumerateChildNodesWithName that returns an array of the matching nodes.
 * This allows subscripting of the form:
 *      NSArray *childrenMatchingName = node[@"name"]
 *
 * or even complex like:
 *      NSArray *siblingsBeginningWithA = node[@"../a*"]
 *
 * @param name An Xpath style path that can include simple regular expressions for matching node names.
 * @see enumerateChildNodesWithName:usingBlock:
 */
- (NSArray *)objectForKeyedSubscript:(NSString *)name NS_AVAILABLE(10_10, 8_0);

/* Returns true if the specified parent is in this node's chain of parents */

- (BOOL)inParentHierarchy:(SKNode *)parent;

- (void)runAction:(SKAction *)action;
- (void)runAction:(SKAction *)action completion:(void (^)())block;
- (void)runAction:(SKAction *)action withKey:(NSString *)key;

- (BOOL)hasActions;
- (SKAction *)actionForKey:(NSString *)key;

- (void)removeActionForKey:(NSString *)key;
- (void)removeAllActions;

- (BOOL)containsPoint:(CGPoint)p;
- (SKNode *)nodeAtPoint:(CGPoint)p;
- (NSArray *)nodesAtPoint:(CGPoint)p;

- (CGPoint)convertPoint:(CGPoint)point fromNode:(SKNode *)node;
- (CGPoint)convertPoint:(CGPoint)point toNode:(SKNode *)node;

/* Returns true if the bounds of this node intersects with the transformed bounds of the other node, otherwise false */

- (BOOL)intersectsNode:(SKNode *)node;

/* Returns true if this node has equivalent content to the other object, otherwise false */

- (BOOL)isEqualToNode:(SKNode *)node;

@end


/**
 Provided for easy transformation of UITouches coordinates to SKNode coordinates should you choose to handle touch events natively.
 */
#if TARGET_OS_IPHONE
//Allow conversion of UITouch coordinates to scene-space
@interface UITouch (SKNodeTouches)
- (CGPoint)locationInNode:(SKNode *)node;
- (CGPoint)previousLocationInNode:(SKNode *)node;
@end
#else
@interface NSEvent (SKNodeEvent)
- (CGPoint)locationInNode:(SKNode *)node;
@end
#endif
