//
//  AppViewController.swift
//  Mediapipe
//
//  Created by Sneha Mahapatra on 9/15/20.
//

#import "AppViewController.h"

@interface AppViewController (){}
@property (weak, nonatomic) IBOutlet UIImageView *AlphabetGif;
@property (weak, nonatomic) IBOutlet UIImageView *PhrasesGif;
@property (weak, nonatomic) IBOutlet UIImageView *HouseHold;
@property (weak, nonatomic) IBOutlet UIImageView *AnimalGIF;
@property (weak, nonatomic) IBOutlet UIImageView *Clothing;
@property (weak, nonatomic) IBOutlet UIImageView *School;
@property (weak, nonatomic) IBOutlet UIImageView *Actions;
@property (weak, nonatomic) IBOutlet UIImageView *Outdoots;
@property (weak, nonatomic) IBOutlet UIImageView *People;

@end

@implementation AppViewController
-(void)viewDidLoad{
    [super viewDidLoad];
    _AlphabetGif.animationImages = [NSArray arrayWithObjects:
                                   [UIImage imageNamed:@"Alphabet/frame_00_delay-0.1s.gif"],
                                   [UIImage imageNamed:@"Alphabet/frame_01_delay-0.1s.gif"],
                                   [UIImage imageNamed:@"Alphabet/frame_02_delay-0.1s.gif"],
                                   [UIImage imageNamed:@"Alphabet/frame_03_delay-0.1s.gif"],
                                   [UIImage imageNamed:@"Alphabet/frame_04_delay-0.1s.gif"],
                                    [UIImage imageNamed:@"Alphabet/frame_05_delay-0.1s.gif"],
                                     [UIImage imageNamed:@"Alphabet/frame_06_delay-0.1s.gif"],
                                     [UIImage imageNamed:@"Alphabet/frame_07_delay-0.1s.gif"],
                                     [UIImage imageNamed:@"Alphabet/frame_08_delay-0.1s.gif"],
                                    [UIImage imageNamed:@"Alphabet/frame_09_delay-0.1s.gif"],
                                     [UIImage imageNamed:@"Alphabet/frame_10_delay-0.1s.gif"],
                                     [UIImage imageNamed:@"Alphabet/frame_11_delay-0.1s.gif"],
                                     [UIImage imageNamed:@"Alphabet/frame_12_delay-0.1s.gif"],
                                     [UIImage imageNamed:@"Alphabet/frame_13_delay-0.1s.gif"],
                                     [UIImage imageNamed:@"Alphabet/frame_14_delay-0.1s.gif"],
                                     [UIImage imageNamed:@"Alphabet/frame_15_delay-0.1s.gif"],
                                    [UIImage imageNamed:@"Alphabet/frame_16_delay-0.1s.gif"],
                                     [UIImage imageNamed:@"Alphabet/frame_17_delay-0.1s.gif"],
                                     [UIImage imageNamed:@"Alphabet/frame_18_delay-0.1s.gif"],
                                    [UIImage imageNamed:@"Alphabet/frame_19_delay-0.1s.gif"],
                                     [UIImage imageNamed:@"Alphabet/frame_20_delay-0.1s.gif"],
                                     [UIImage imageNamed:@"Alphabet/frame_21_delay-0.1s.gif"],
                                    [UIImage imageNamed:@"Alphabet/frame_22_delay-0.1s.gif"],
                                     [UIImage imageNamed:@"Alphabet/frame_23_delay-0.1s.gif"],
                                    [UIImage imageNamed:@"Alphabet/frame_24_delay-0.1s.gif"],
                                 [UIImage imageNamed:@"Alphabet/frame_25_delay-0.1s.gif"],
                                [UIImage imageNamed:@"Alphabet/frame_26_delay-0.1s.gif"],
                                [UIImage imageNamed:@"Alphabet/frame_27_delay-0.1s.gif"],
                               [UIImage imageNamed:@"Alphabet/frame_28_delay-0.1s.gif"],
                               [UIImage imageNamed:@"Alphabet/frame_29_delay-0.1s.gif"],
                                [UIImage imageNamed:@"Alphabet/frame_30_delay-0.1s.gif"],
                                [UIImage imageNamed:@"Alphabet/frame_31_delay-0.1s.gif"],
                                    [UIImage imageNamed:@"Alphabet/frame_30_delay-0.1s.gif"],
                                [UIImage imageNamed:@"Alphabet/frame_32_delay-0.1s.gif"],
                                [UIImage imageNamed:@"Alphabet/frame_33_delay-0.1s.gif"],
                                    [UIImage imageNamed:@"Alphabet/frame_34_delay-0.1s.gif"],
                                [UIImage imageNamed:@"Alphabet/frame_34_delay-0.1s.gif"],nil];
                                                                                                                                        
   _AlphabetGif.animationDuration = 3.0f;
   //_PhrasesGif.animationRepeatCount = 100;
    [_AlphabetGif startAnimating];
    [self.view addSubview: _AlphabetGif];
    
    _PhrasesGif.animationImages = [NSArray arrayWithObjects:
                                    [UIImage imageNamed:@"Phrases/frame_00_delay-0.1s.gif"],
                                    [UIImage imageNamed:@"Phrases/frame_01_delay-0.1s.gif"],
                                    [UIImage imageNamed:@"Phrases/frame_02_delay-0.1s.gif"],
                                    [UIImage imageNamed:@"Phrases/frame_03_delay-0.1s.gif"],
                                    [UIImage imageNamed:@"Phrases/frame_04_delay-0.1s.gif"],
                                     [UIImage imageNamed:@"Phrases/frame_05_delay-0.1s.gif"],
                                      [UIImage imageNamed:@"Phrases/frame_06_delay-0.1s.gif"],
                                      [UIImage imageNamed:@"Phrases/frame_07_delay-0.1s.gif"],
                                      [UIImage imageNamed:@"Phrases/frame_08_delay-0.1s.gif"],
                                     [UIImage imageNamed:@"Phrases/frame_09_delay-0.1s.gif"],
                                      [UIImage imageNamed:@"Phrases/frame_10_delay-0.1s.gif"],
                                      [UIImage imageNamed:@"Phrases/frame_11_delay-0.1s.gif"],
                                      [UIImage imageNamed:@"Phrases/frame_12_delay-0.1s.gif"],
                                      nil];
                                                                                
    _PhrasesGif.animationDuration = 3.0f;
   //  _PhrasesGif.animationRepeatCount = 100;
     [_PhrasesGif startAnimating];
     [self.view addSubview: _PhrasesGif];
    
    _HouseHold.animationImages = [NSArray arrayWithObjects:
                                     [UIImage imageNamed:@"HouseHold/frame_00_delay-0.1s.gif"],
                                     [UIImage imageNamed:@"HouseHold/frame_01_delay-0.1s.gif"],
                                     [UIImage imageNamed:@"HouseHold/frame_02_delay-0.1s.gif"],
                                     [UIImage imageNamed:@"HouseHold/frame_03_delay-0.1s.gif"],
                                     [UIImage imageNamed:@"HouseHold/frame_04_delay-0.1s.gif"],
                                      [UIImage imageNamed:@"HouseHold/frame_05_delay-0.1s.gif"],
                                       [UIImage imageNamed:@"HouseHold/frame_06_delay-0.1s.gif"],
                                       [UIImage imageNamed:@"HouseHold/frame_07_delay-0.1s.gif"],
                                       [UIImage imageNamed:@"HouseHold/frame_08_delay-0.1s.gif"],
                                      [UIImage imageNamed:@"HouseHold/frame_09_delay-0.1s.gif"],
                                       [UIImage imageNamed:@"HouseHold/frame_10_delay-0.1s.gif"],
                                       [UIImage imageNamed:@"HouseHold/frame_11_delay-0.1s.gif"],
                                       [UIImage imageNamed:@"HouseHold/frame_12_delay-0.1s.gif"],
                                  [UIImage imageNamed:@"HouseHold/frame_13_delay-0.1s.gif"],
                                  [UIImage imageNamed:@"HouseHold/frame_14_delay-0.1s.gif"],
                                  [UIImage imageNamed:@"HouseHold/frame_15_delay-0.1s.gif"],
                                       nil];
                                                                                 
     _HouseHold.animationDuration = 3.0f;
    //  _PhrasesGif.animationRepeatCount = 100;
      [_HouseHold startAnimating];
      [self.view addSubview: _HouseHold];
    
    _AnimalGIF.animationImages = [NSArray arrayWithObjects:
                                     [UIImage imageNamed:@"AnimalGIF/frame_00_delay-0.1s.gif"],
                                     [UIImage imageNamed:@"AnimalGIF/frame_01_delay-0.1s.gif"],
                                     [UIImage imageNamed:@"AnimalGIF/frame_02_delay-0.1s.gif"],
                                     [UIImage imageNamed:@"AnimalGIF/frame_03_delay-0.1s.gif"],
                                     [UIImage imageNamed:@"AnimalGIF/frame_04_delay-0.1s.gif"],
                                      [UIImage imageNamed:@"AnimalGIF/frame_05_delay-0.1s.gif"],
                                       [UIImage imageNamed:@"AnimalGIF/frame_06_delay-0.1s.gif"],
                                       [UIImage imageNamed:@"AnimalGIF/frame_07_delay-0.1s.gif"],
                                       [UIImage imageNamed:@"AnimalGIF/frame_08_delay-0.1s.gif"],
                                      [UIImage imageNamed:@"AnimalGIF/frame_09_delay-0.1s.gif"],
                                       [UIImage imageNamed:@"AnimalGIF/frame_10_delay-0.1s.gif"],
                                       [UIImage imageNamed:@"AnimalGIF/frame_11_delay-0.1s.gif"],
                                       [UIImage imageNamed:@"AnimalGIF/frame_12_delay-0.1s.gif"],
                                  [UIImage imageNamed:@"AnimalGIF/frame_13_delay-0.1s.gif"],
                                  [UIImage imageNamed:@"AnimalGIF/frame_14_delay-0.1s.gif"],
                                       nil];
                                                                                 
     _AnimalGIF.animationDuration = 3.0f;
    //  _PhrasesGif.animationRepeatCount = 100;
      [_AnimalGIF startAnimating];
      [self.view addSubview: _AnimalGIF];
    
    _Clothing.animationImages = [NSArray arrayWithObjects:
                                     [UIImage imageNamed:@"Clothing/frame_00_delay-0.1s.gif"],
                                     [UIImage imageNamed:@"Clothing/frame_01_delay-0.1s.gif"],
                                     [UIImage imageNamed:@"Clothing/frame_02_delay-0.1s.gif"],
                                     [UIImage imageNamed:@"Clothing/frame_03_delay-0.1s.gif"],
                                     [UIImage imageNamed:@"Clothing/frame_04_delay-0.1s.gif"],
                                      [UIImage imageNamed:@"Clothing/frame_05_delay-0.1s.gif"],
                                       [UIImage imageNamed:@"Clothing/frame_06_delay-0.1s.gif"],
                                       [UIImage imageNamed:@"Clothing/frame_07_delay-0.1s.gif"],
                                       [UIImage imageNamed:@"Clothing/frame_08_delay-0.1s.gif"],
                                      [UIImage imageNamed:@"Clothing/frame_09_delay-0.1s.gif"],
                                       [UIImage imageNamed:@"Clothing/frame_10_delay-0.1s.gif"],
                                       [UIImage imageNamed:@"Clothing/frame_11_delay-0.1s.gif"],
                                       nil];
                                                                                 
     _Clothing.animationDuration = 3.0f;
    //  _PhrasesGif.animationRepeatCount = 100;
      [_Clothing startAnimating];
      [self.view addSubview: _Clothing];
    
    _School .animationImages = [NSArray arrayWithObjects:
                                        [UIImage imageNamed:@"SchoolGIF/frame_00_delay-0.1s.gif"],
                                        [UIImage imageNamed:@"SchoolGIF/frame_01_delay-0.1s.gif"],
                                        [UIImage imageNamed:@"SchoolGIF/frame_02_delay-0.1s.gif"],
                                        [UIImage imageNamed:@"SchoolGIF/frame_03_delay-0.1s.gif"],
                                        [UIImage imageNamed:@"SchoolGIF/frame_04_delay-0.1s.gif"],
                                         [UIImage imageNamed:@"SchoolGIF/frame_05_delay-0.1s.gif"],
                                          [UIImage imageNamed:@"SchoolGIF/frame_06_delay-0.1s.gif"],
                                          [UIImage imageNamed:@"SchoolGIF/frame_07_delay-0.1s.gif"],
                                          [UIImage imageNamed:@"SchoolGIF/frame_08_delay-0.1s.gif"],
                                         [UIImage imageNamed:@"SchoolGIF/frame_09_delay-0.1s.gif"],
                                          [UIImage imageNamed:@"SchoolGIF/frame_10_delay-0.1s.gif"],
                                          [UIImage imageNamed:@"AnimalGIF/frame_11_delay-0.1s.gif"],
                                          [UIImage imageNamed:@"AnimalGIF/frame_12_delay-0.1s.gif"],
                                     [UIImage imageNamed:@"AnimalGIF/frame_13_delay-0.1s.gif"],
                                     [UIImage imageNamed:@"AnimalGIF/frame_14_delay-0.1s.gif"],
                                          nil];
                                                                                    
        _School.animationDuration = 3.0f;
       //  _PhrasesGif.animationRepeatCount = 100;
         [_School startAnimating];
         [self.view addSubview: _School];
    
    _Actions.animationImages = [NSArray arrayWithObjects:
                                      [UIImage imageNamed:@"ActionsGIF/frame_00_delay-0.1s.gif"],
                                      [UIImage imageNamed:@"ActionsGIF/frame_01_delay-0.1s.gif"],
                                      [UIImage imageNamed:@"ActionsGIF/frame_02_delay-0.1s.gif"],
                                      [UIImage imageNamed:@"ActionsGIF/frame_03_delay-0.1s.gif"],
                                      [UIImage imageNamed:@"ActionsGIF/frame_04_delay-0.1s.gif"],
                                       [UIImage imageNamed:@"ActionsGIF/frame_05_delay-0.1s.gif"],
                                        [UIImage imageNamed:@"ActionsGIF/frame_06_delay-0.1s.gif"],
                                        [UIImage imageNamed:@"ActionsGIF/frame_07_delay-0.1s.gif"],
                                        [UIImage imageNamed:@"ActionsGIF/frame_08_delay-0.1s.gif"],
                                       [UIImage imageNamed:@"ActionsGIF/frame_09_delay-0.1s.gif"],
                                        [UIImage imageNamed:@"ActionsGIF/frame_10_delay-0.1s.gif"],
                                        [UIImage imageNamed:@"ActionsGIF/frame_11_delay-0.1s.gif"],
                                        [UIImage imageNamed:@"ActionsGIF/frame_12_delay-0.1s.gif"],
                                        [UIImage imageNamed:@"ActionsGIF/frame_13_delay-0.1s.gif"],
                                        [UIImage imageNamed:@"ActionsGIF/frame_14_delay-0.1s.gif"],
                                        [UIImage imageNamed:@"ActionsGIF/frame_15_delay-0.1s.gif"],
                                       [UIImage imageNamed:@"ActionsGIF/frame_16_delay-0.1s.gif"],
                                        [UIImage imageNamed:@"ActionsGIF/frame_17_delay-0.1s.gif"],
                                        [UIImage imageNamed:@"ActionsGIF/frame_18_delay-0.1s.gif"],
                                       [UIImage imageNamed:@"ActionsGIF/frame_19_delay-0.1s.gif"],
                                        [UIImage imageNamed:@"ActionsGIF/frame_20_delay-0.1s.gif"],
                                        [UIImage imageNamed:@"ActionsGIF/frame_21_delay-0.1s.gif"],nil];
                                                                                                                                           
      _Actions.animationDuration = 3.0f;
      //_PhrasesGif.animationRepeatCount = 100;
       [_Actions startAnimating];
       [self.view addSubview: _Actions];
    
    _Outdoots.animationImages = [NSArray arrayWithObjects:
                                    [UIImage imageNamed:@"OutdoorsGIF/frame_00_delay-0.1s.gif"],
                                    [UIImage imageNamed:@"OutdoorsGIF/frame_01_delay-0.1s.gif"],
                                    [UIImage imageNamed:@"OutdoorsGIF/frame_02_delay-0.1s.gif"],
                                    [UIImage imageNamed:@"OutdoorsGIF/frame_03_delay-0.1s.gif"],
                                    [UIImage imageNamed:@"OutdoorsGIF/frame_04_delay-0.1s.gif"],
                                     [UIImage imageNamed:@"OutdoorsGIF/frame_05_delay-0.1s.gif"],
                                      [UIImage imageNamed:@"OutdoorsGIF/frame_06_delay-0.1s.gif"],
                                      [UIImage imageNamed:@"OutdoorsGIF/frame_07_delay-0.1s.gif"],
                                      [UIImage imageNamed:@"OutdoorsGIF/frame_08_delay-0.1s.gif"],
                                     [UIImage imageNamed:@"OutdoorsGIF/frame_09_delay-0.1s.gif"],
                                      [UIImage imageNamed:@"OutdoorsGIF/frame_10_delay-0.1s.gif"],
                                      [UIImage imageNamed:@"OutdoorsGIF/frame_11_delay-0.1s.gif"],
                                      [UIImage imageNamed:@"OutdoorsGIF/frame_12_delay-0.1s.gif"],
                                      [UIImage imageNamed:@"OutdoorsGIF/frame_13_delay-0.1s.gif"],
                                      [UIImage imageNamed:@"OutdoorsGIF/frame_14_delay-0.1s.gif"],
                                      [UIImage imageNamed:@"OutdoorsGIF/frame_15_delay-0.1s.gif"],
                                     [UIImage imageNamed:@"OutdoorsGIF/frame_16_delay-0.1s.gif"],
                                      [UIImage imageNamed:@"OutdoorsGIF/frame_17_delay-0.1s.gif"],
                                      [UIImage imageNamed:@"OutdoorsGIF/frame_18_delay-0.1s.gif"],
                                     [UIImage imageNamed:@"OutdoorsGIF/frame_19_delay-0.1s.gif"],
                                      [UIImage imageNamed:@"OutdoorsGIF/frame_20_delay-0.1s.gif"],
                                      [UIImage imageNamed:@"OutdoorsGIF/frame_21_delay-0.1s.gif"],nil];
                                                                                                                                         
    _Outdoots.animationDuration = 3.0f;
    //_PhrasesGif.animationRepeatCount = 100;
     [_Outdoots startAnimating];
     [self.view addSubview: _Outdoots];
    
    _People.animationImages = [NSArray arrayWithObjects:
                                     [UIImage imageNamed:@"PeopleGIF/frame_00_delay-0.1s.gif"],
                                     [UIImage imageNamed:@"PeopleGIF/frame_01_delay-0.1s.gif"],
                                     [UIImage imageNamed:@"PeopleGIF/frame_02_delay-0.1s.gif"],
                                     [UIImage imageNamed:@"PeopleGIF/frame_03_delay-0.1s.gif"],
                                     [UIImage imageNamed:@"PeopleGIF/frame_04_delay-0.1s.gif"],
                                      [UIImage imageNamed:@"PeopleGIF/frame_05_delay-0.1s.gif"],
                                       [UIImage imageNamed:@"PeopleGIF/frame_06_delay-0.1s.gif"],
                                       [UIImage imageNamed:@"PeopleGIF/frame_07_delay-0.1s.gif"],
                                       [UIImage imageNamed:@"PeopleGIF/frame_08_delay-0.1s.gif"],
                                      [UIImage imageNamed:@"PeopleGIF/frame_09_delay-0.1s.gif"],nil];
                                                                                 
     _People.animationDuration = 3.0f;
    //  _PhrasesGif.animationRepeatCount = 100;
      [_People startAnimating];
      [self.view addSubview: _People];
}

@end
