//
//  GameScene.swift
//  trail
//
//  Created by Vaish Raman on 1/17/15.
//  Copyright (c) 2015 DHackers Unchained. All rights reserved.
//

import SpriteKit

class GameScene: SKScene {
    
    var ball = SKSpriteNode();
    var grass = SKSpriteNode();
    let ballCategory: UInt32 = 0x1 << 0
    let logCategory: UInt32 = 0x1 << 1


    
    override func didMoveToView(view: SKView) {
        /* Setup your scene here */
        let myLabel = SKLabelNode(fontNamed:"Chalkduster")
        self.backgroundColor = UIColor.blueColor()
        myLabel.text = "Hello, World!";
        myLabel.fontSize = 65;
        myLabel.position = CGPoint(x:CGRectGetMidX(self.frame), y:CGRectGetMidY(self.frame));
        
        self.addChild(myLabel)
        
        //Ball
        var BallTexture = SKTexture(imageNamed: "Ball1.png")
        
        BallTexture.filteringMode = SKTextureFilteringMode.Nearest
        
        ball = SKSpriteNode(texture: BallTexture);
        ball.setScale(0.25);
        ball.position = CGPoint(x:self.frame.size.width * 0.4, y: self.frame.size.height * 0.1)
        
        ball.physicsBody?.categoryBitMask = ballCategory;
        ball.physicsBody?.collisionBitMask = ballCategory | logCategory;
        ball.physicsBody?.contactTestBitMask = ballCategory | logCategory;
        
        
        ball.physicsBody = SKPhysicsBody(circleOfRadius: 22.45);
        ball.physicsBody?.allowsRotation = false;
        ball.physicsBody?.dynamic = true;
        
        let action = SKAction.rotateByAngle(CGFloat(-5), duration:1)
        
        ball.runAction(SKAction.repeatActionForever(action))
        
        self.addChild(ball);

        var GrassTexture = SKTexture(imageNamed: "mygrass.jpeg");
        
        GrassTexture.filteringMode = SKTextureFilteringMode.Nearest
        
        grass = SKSpriteNode(texture: GrassTexture);
        grass.setScale(1);
        grass.position = CGPoint(x:self.frame.size.width * 0.5, y: self.frame.size.height * 0.065)
        
        self.addChild(grass);
        
        grass.physicsBody = SKPhysicsBody(rectangleOfSize: CGSizeMake(self.frame.size.width, GrassTexture.size().height))
        //grass.physicsBody?.friction = 0.0
        grass.physicsBody?.dynamic = false;
        
        self.addChild(grass);

        
    }
    
    override func touchesBegan(touches: NSSet, withEvent event: UIEvent) {
        /* Called when a touch begins */

        
        for touch: AnyObject in touches {
            
            let location = touch.locationInNode(self)
            ball.physicsBody?.velocity = CGVectorMake(0, 0);
            ball.physicsBody?.applyImpulse(CGVectorMake(0, 110.0));
            
            
        }

        
        /*for touch: AnyObject in touches {
            let location = touch.locationInNode(self)
            
            let sprite = SKSpriteNode(imageNamed:"Spaceship")
            
            sprite.xScale = 0.5
            sprite.yScale = 0.5
            sprite.position = location
            
            let action = SKAction.rotateByAngle(CGFloat(M_PI), duration:1)
            
            sprite.runAction(SKAction.repeatActionForever(action))
            
            self.addChild(sprite)
        }*/
    }
   
    override func update(currentTime: CFTimeInterval) {
        /* Called before each frame is rendered */
    }
}
