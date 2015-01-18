//
//  GameScene.swift
//  Learn123
//
//  Created by Vaish Raman on 1/16/15.
//  Copyright (c) 2015 Vaish Raman. All rights reserved.
//

import SpriteKit
import Foundation

class GameScene: SKScene, SKPhysicsContactDelegate {

    
    
    
    var ball = SKSpriteNode();
    var grass = SKSpriteNode();
    var log1 = SKSpriteNode();
    var log2 = SKSpriteNode();
    var log3 = SKSpriteNode();
    //var score = convenience init(timeIntervalSinceNow seconds: 1);

    //var addtime = 0.0;
    //var hill = SKSpriteNode();
   // var score = 0;
    
    let ballCategory: UInt32 = 0x1 << 0
    let logCategory: UInt32 = 0x1 << 1
    var run = true;
    
    var parentVC: UIViewController?
    
    override func didMoveToView(view: SKView) {
        
        self.physicsWorld.contactDelegate = self;
        
        //Physics
        self.physicsWorld.gravity = CGVectorMake(0.0, -9.0)
        
        //Ball
        var BallTexture = SKTexture(imageNamed: "penguin.png")
        
        BallTexture.filteringMode = SKTextureFilteringMode.Nearest
        
        ball = SKSpriteNode(texture: BallTexture);
        ball.setScale(0.25);
        ball.position = CGPoint(x:self.frame.size.width * 0.42, y: self.frame.size.height * 0.1)
        
        ball.physicsBody?.categoryBitMask = ballCategory;
        ball.physicsBody?.collisionBitMask = ballCategory | logCategory;
        ball.physicsBody?.contactTestBitMask = ballCategory | logCategory;
        
        
        ball.physicsBody = SKPhysicsBody(circleOfRadius:ball.size.height/4);
        ball.physicsBody?.allowsRotation = false;
        ball.physicsBody?.dynamic = true;
        
        let action = SKAction.rotateByAngle(CGFloat(-10), duration:1)
        
        ball.runAction(SKAction.repeatActionForever(action))
        
        self.addChild(ball);
        
        // Create ground
        
        
        var GrassTexture = SKTexture(imageNamed: "ocean.jpg");
        
        GrassTexture.filteringMode = SKTextureFilteringMode.Nearest
        
        grass = SKSpriteNode(texture: GrassTexture);
        grass.setScale(1);
        grass.position = CGPoint(x:self.frame.size.width * 0.5, y: self.frame.size.height * 0.065)
        
        
        grass.physicsBody = SKPhysicsBody(rectangleOfSize: CGSizeMake(self.frame.size.width, GrassTexture.size().height))
        grass.physicsBody?.friction = 0.0
        
        grass.physicsBody?.dynamic = false;
        
        self.addChild(grass);
        
        //Log
        
        
        
        /*var HillTexture = SKTexture(imageNamed: "hill.png")
        
        HillTexture.filteringMode = SKTextureFilteringMode.Nearest
        
        hill = SKSpriteNode(texture: HillTexture);
        hill.setScale(0.01);
        hill.position = CGPoint(x:self.frame.size.width * 0.5, y: self.frame.size.height * 0.5)
        hill.physicsBody = SKPhysicsBody(texture: HillTexture, size: HillTexture.size());
        hill.physicsBody?.velocity = CGVectorMake(-100, 0);
        
        self.addChild(hill);*/
        
        let Background = SKTexture(imageNamed: "bg3.jpg")
        Background.filteringMode = .Nearest
        
        let BackgroundMove = SKAction.moveByX(-self.frame.size.width, y:0 , duration: 20)
        let BackgroundReset = SKAction.moveByX(self.frame.size.width, y:0 , duration: 0.0)
        let BackgroundMoveAndResetForever = SKAction.repeatActionForever(SKAction.sequence([BackgroundMove,BackgroundReset]))
        
        for var i:CGFloat = 0; i < Background.size().width ; ++i {
            let sprite = SKSpriteNode(texture: Background)
            sprite.size = CGSize( width: (self.frame.size.width*2.2), height: self.frame.size.height)
            sprite.position = CGPointMake((self.frame.size.width*1.0) * i, self.frame.size.height/2 + 111)
            sprite.zPosition = -30
            sprite.runAction(BackgroundMoveAndResetForever)
            self.addChild(sprite)
        }
        /* var timerA = NSTimer.scheduledTimerWithTimeInterval(1/3, target: self, selector: Selector("UpDateScore"), userInfo: nil, repeats: true)*/
        
        //var pause = Int(arc4random_uniform(7));
        //println(pause);
        var timer = NSTimer.scheduledTimerWithTimeInterval(0.9, target: self, selector: Selector("CreateNewObstacle"), userInfo: nil, repeats: true)
        
        
    }
    
    // func UpDateScore() {
    //   score = score + 1;
    //}
    func CreateNewObstacle() {
        
        var pause = Int(arc4random_uniform(6) + 1);
        
        
        switch (pause) {
        case (1):
            var LogTexture1 = SKTexture(imageNamed: "icicles1.png")
            LogTexture1.filteringMode = SKTextureFilteringMode.Nearest
            log1 = SKSpriteNode(texture: LogTexture1);
            log1.setScale(0.5)
            log1.physicsBody?.dynamic = false;
            log1.physicsBody?.collisionBitMask = logCategory;
            log1.position = CGPoint(x:self.frame.size.width * 0.9, y: self.frame.size.height * 0.19)
            
            log1.physicsBody = SKPhysicsBody (rectangleOfSize: CGSizeMake(200/4, 150/4))
            log1.physicsBody?.velocity = CGVectorMake(-300.0, 0);
            log1.physicsBody?.affectedByGravity = false;
            log1.physicsBody?.usesPreciseCollisionDetection = false;
            
            self.addChild(log1);
            
            log1.physicsBody?.contactTestBitMask = ballCategory;
        case (2):
            var LogTexture2 = SKTexture(imageNamed: "icicles2.png")
            LogTexture2.filteringMode = SKTextureFilteringMode.Nearest
            log2 = SKSpriteNode(texture: LogTexture2);
            log2.setScale(1/3)
            log2.physicsBody?.dynamic = false;
            log2.physicsBody?.collisionBitMask = logCategory;
            log2.position = CGPoint(x:self.frame.size.width * 0.9, y: self.frame.size.height * 0.20)
            log2.physicsBody = SKPhysicsBody (rectangleOfSize: CGSizeMake(140/6, 353/6))
            
            log2.physicsBody?.velocity = CGVectorMake(-300.0, 0);
            log2.physicsBody?.affectedByGravity = false;
            log2.physicsBody?.usesPreciseCollisionDetection = false;
            
            self.addChild(log2);
            
            log2.physicsBody?.contactTestBitMask = ballCategory;
        case (3):
            var LogTexture3 = SKTexture(imageNamed: "icicles3.png")
            LogTexture3.filteringMode = SKTextureFilteringMode.Nearest
            log3 = SKSpriteNode(texture: LogTexture3);
            log3.setScale(1/3)
            log3.physicsBody?.dynamic = false;
            log3.physicsBody?.collisionBitMask = logCategory;
            log3.position = CGPoint(x:self.frame.size.width * 0.9, y: self.frame.size.height * 0.185)
            log3.physicsBody = SKPhysicsBody (rectangleOfSize: CGSizeMake(200/6, 300/6))
            
            log3.physicsBody?.velocity = CGVectorMake(-300.0, 0);
            log3.physicsBody?.affectedByGravity = false;
            log3.physicsBody?.usesPreciseCollisionDetection = false;
            
            self.addChild(log3);
            log3.physicsBody?.contactTestBitMask = ballCategory;
        case(4):
            println("hi");
            //log.physicsBody?.contactTestBitMask = ballCategory;
        case(5):
            println("hi");
            //log.physicsBody?.contactTestBitMask = ballCategory;
        case(6):
            println("hi");
            //log.physicsBody?.contactTestBitMask = ballCategory;
        default:
            println("hola");
            //log.physicsBody?.contactTestBitMask = ballCategory;
            
        }
        
    }
    
    
    /*log = SKSpriteNode(texture: LogTexture);
    log.setScale(0.2)
    log.physicsBody?.dynamic = false;
    log.physicsBody?.collisionBitMask = logCategory;
    log.position = CGPoint(x:self.frame.size.width * 0.7, y: self.frame.size.height * 0.20)
    
    log.physicsBody = SKPhysicsBody (rectangleOfSize: CGSizeMake(LogTexture.size().width/5, LogTexture.size().height/5))
    log.physicsBody?.velocity = CGVectorMake(-100, 0);
    log.physicsBody?.affectedByGravity = false;
    log.physicsBody?.usesPreciseCollisionDetection = false;
    
    self.addChild(log);
    log.physicsBody?.contactTestBitMask = ballCategory;*/
    
    
    
    func didBeginContact(contact: SKPhysicsContact) {
        var firstBody = contact.bodyA;
        var secondBody = contact.bodyB;
        
        if (((firstBody.categoryBitMask & logCategory) != 0) && (secondBody.categoryBitMask & ballCategory) != 0) {
            println("collision occured");
            run = false;
            
            let storyboard = UIStoryboard(name: "Main", bundle: nil)
            let vc = storyboard.instantiateViewControllerWithIdentifier("GameOver") as UIViewController
            
            parentVC?.presentViewController(vc, animated: true, completion: nil)
        }
        println("contact occured");
    }
    
    override func touchesBegan(touches: NSSet, withEvent event: UIEvent) {
        /* Called when a touch begins */
        
        for touch: AnyObject in touches {
            
            let location = touch.locationInNode(self)
            if(ball.position.y <= 180.0) {
                ball.physicsBody?.velocity = CGVectorMake(0, 0);
                ball.physicsBody?.applyImpulse(CGVectorMake(0, 14.0));
            }
            
        }
    }
    
    
    override func update(currentTime: CFTimeInterval) {
        // Called before each frame is rendered
        
    }
}