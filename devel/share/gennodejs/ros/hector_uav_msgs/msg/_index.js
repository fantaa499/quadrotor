
"use strict";

let Compass = require('./Compass.js');
let PositionXYCommand = require('./PositionXYCommand.js');
let ThrustCommand = require('./ThrustCommand.js');
let Supply = require('./Supply.js');
let MotorPWM = require('./MotorPWM.js');
let HeadingCommand = require('./HeadingCommand.js');
let Altimeter = require('./Altimeter.js');
let MotorStatus = require('./MotorStatus.js');
let MotorCommand = require('./MotorCommand.js');
let RawImu = require('./RawImu.js');
let HeightCommand = require('./HeightCommand.js');
let VelocityXYCommand = require('./VelocityXYCommand.js');
let RC = require('./RC.js');
let ServoCommand = require('./ServoCommand.js');
let RawMagnetic = require('./RawMagnetic.js');
let RawRC = require('./RawRC.js');
let ControllerState = require('./ControllerState.js');
let YawrateCommand = require('./YawrateCommand.js');
let VelocityZCommand = require('./VelocityZCommand.js');
let RuddersCommand = require('./RuddersCommand.js');
let AttitudeCommand = require('./AttitudeCommand.js');
let TakeoffActionResult = require('./TakeoffActionResult.js');
let LandingResult = require('./LandingResult.js');
let PoseAction = require('./PoseAction.js');
let PoseActionGoal = require('./PoseActionGoal.js');
let PoseActionFeedback = require('./PoseActionFeedback.js');
let LandingAction = require('./LandingAction.js');
let PoseActionResult = require('./PoseActionResult.js');
let LandingActionFeedback = require('./LandingActionFeedback.js');
let TakeoffResult = require('./TakeoffResult.js');
let TakeoffGoal = require('./TakeoffGoal.js');
let TakeoffAction = require('./TakeoffAction.js');
let PoseGoal = require('./PoseGoal.js');
let PoseResult = require('./PoseResult.js');
let LandingGoal = require('./LandingGoal.js');
let TakeoffActionGoal = require('./TakeoffActionGoal.js');
let TakeoffActionFeedback = require('./TakeoffActionFeedback.js');
let LandingActionGoal = require('./LandingActionGoal.js');
let LandingActionResult = require('./LandingActionResult.js');
let LandingFeedback = require('./LandingFeedback.js');
let TakeoffFeedback = require('./TakeoffFeedback.js');
let PoseFeedback = require('./PoseFeedback.js');

module.exports = {
  Compass: Compass,
  PositionXYCommand: PositionXYCommand,
  ThrustCommand: ThrustCommand,
  Supply: Supply,
  MotorPWM: MotorPWM,
  HeadingCommand: HeadingCommand,
  Altimeter: Altimeter,
  MotorStatus: MotorStatus,
  MotorCommand: MotorCommand,
  RawImu: RawImu,
  HeightCommand: HeightCommand,
  VelocityXYCommand: VelocityXYCommand,
  RC: RC,
  ServoCommand: ServoCommand,
  RawMagnetic: RawMagnetic,
  RawRC: RawRC,
  ControllerState: ControllerState,
  YawrateCommand: YawrateCommand,
  VelocityZCommand: VelocityZCommand,
  RuddersCommand: RuddersCommand,
  AttitudeCommand: AttitudeCommand,
  TakeoffActionResult: TakeoffActionResult,
  LandingResult: LandingResult,
  PoseAction: PoseAction,
  PoseActionGoal: PoseActionGoal,
  PoseActionFeedback: PoseActionFeedback,
  LandingAction: LandingAction,
  PoseActionResult: PoseActionResult,
  LandingActionFeedback: LandingActionFeedback,
  TakeoffResult: TakeoffResult,
  TakeoffGoal: TakeoffGoal,
  TakeoffAction: TakeoffAction,
  PoseGoal: PoseGoal,
  PoseResult: PoseResult,
  LandingGoal: LandingGoal,
  TakeoffActionGoal: TakeoffActionGoal,
  TakeoffActionFeedback: TakeoffActionFeedback,
  LandingActionGoal: LandingActionGoal,
  LandingActionResult: LandingActionResult,
  LandingFeedback: LandingFeedback,
  TakeoffFeedback: TakeoffFeedback,
  PoseFeedback: PoseFeedback,
};
