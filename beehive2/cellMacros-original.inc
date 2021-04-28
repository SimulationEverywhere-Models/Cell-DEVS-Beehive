% This file holds macros to get temperature of the origin cell and other helper macros
% Ambient temperature is 28 degrees celcius with each bee adding 1 degree to the area (total of 9)
#BeginMacro(temp)
28 + if(remainder(remainder((0,0),100), 10) >= 1 AND remainder(remainder((0,0),100), 10) <= 8, 1, 0) + 
  if(remainder(remainder((-1,-1),100), 10) = 9, trunc(remainder((-1,-1),100) / 10), 0) +
  if(remainder(remainder((-1,0),100), 10) = 9, trunc(remainder((-1,0),100) / 10), 0) +
  if(remainder(remainder((-1,1),100), 10) = 9, trunc(remainder((-1,1),100) / 10), 0) +
  if(remainder(remainder((0,1),100), 10) = 9, trunc(remainder((0,1),100) / 10), 0) +
  if(remainder(remainder((1,1),100), 10) = 9, trunc(remainder((1,1),100) / 10), 0) +
  if(remainder(remainder((1,0),100), 10) = 9, trunc(remainder((1,0),100) / 10), 0) +
  if(remainder(remainder((1,-1),100), 10) = 9, trunc(remainder((1,-1),100) / 10), 0) +
  if(remainder(remainder((0,-1),100), 10) = 9, trunc(remainder((0,-1),100) / 10), 0)
#EndMacro

% Gets the bee indents from cells around blank cell
% if a neighbour's M is above 2 and direction is at origin; there is a bee with a movement indent here
#BeginMacro(getBlankM)
0 + 
  if(trunc(remainder((-1,-1),100)/10) >= 1 AND remainder(remainder((-1,-1),100), 10) = 5, 1, 0) + 
  if(trunc(remainder((-1,0),100)/10)  >= 1 AND remainder(remainder((-1,0),100), 10)  = 6, 1, 0) + 
  if(trunc(remainder((-1,1),100)/10)  >= 1 AND remainder(remainder((-1,1),100), 10)  = 7, 1, 0) + 
  if(trunc(remainder((0,1),100)/10)   >= 1 AND remainder(remainder((0,1),100), 10)   = 8, 1, 0) + 
  if(trunc(remainder((1,1),100)/10)   >= 1 AND remainder(remainder((1,1),100), 10)   = 1, 1, 0) + 
  if(trunc(remainder((1,0),100)/10)   >= 1 AND remainder(remainder((1,0),100), 10)   = 2, 1, 0) + 
  if(trunc(remainder((1,-1),100)/10)  >= 1 AND remainder(remainder((1,-1),100), 10)  = 3, 1, 0) + 
  if(trunc(remainder((0,-1),100)/10)  >= 1 AND remainder(remainder((0,-1),100), 10)  = 4, 1, 0)
#EndMacro

% Return the direction (D) of the Bee entering blank cell
% if a neighbour's M is 4 and direction is at origin; there is a bee moving here
#BeginMacro(beeMoveD)
0 + 
  if(trunc(remainder((-1,-1),100)/10) = 4 AND remainder(remainder((-1,-1),100), 10) = 5, 5, 0) + 
  if(trunc(remainder((-1,0),100)/10)  = 4 AND remainder(remainder((-1,0),100), 10)  = 6, 6, 0) + 
  if(trunc(remainder((-1,1),100)/10)  = 4 AND remainder(remainder((-1,1),100), 10)  = 7, 7, 0) + 
  if(trunc(remainder((0,1),100)/10)   = 4 AND remainder(remainder((0,1),100), 10)   = 8, 8, 0) + 
  if(trunc(remainder((1,1),100)/10)   = 4 AND remainder(remainder((1,1),100), 10)   = 1, 1, 0) + 
  if(trunc(remainder((1,0),100)/10)   = 4 AND remainder(remainder((1,0),100), 10)   = 2, 2, 0) + 
  if(trunc(remainder((1,-1),100)/10)  = 4 AND remainder(remainder((1,-1),100), 10)  = 3, 3, 0) + 
  if(trunc(remainder((0,-1),100)/10)  = 4 AND remainder(remainder((0,-1),100), 10)  = 4, 4, 0)
#EndMacro

% Determines whether origin cell is a bee or not by checking encoded Direction
% Returns boolean
#BeginMacro(isBee)
remainder(remainder((0,0),100), 10) >= 1 AND remainder(remainder((0,0),100), 10) <= 8
#EndMacro

% Determines whether origin cell is a blank cell
% Returns boolean
#BeginMacro(isBlank)
remainder(remainder((0,0),100), 10) = 0
#EndMacro

% Gets the wait time (real) for a bee, sigmoid function dependent on temperature. Values come from [1]
#BeginMacro(waitTime)
(power(3.09 - 0.0403 * trunc((0,0) / 100),-27)/(power(3.09 - 0.0403 * trunc((0,0) / 100),-27) + power(1.79,-27))) * 22.5 + 0.645
#EndMacro

% Chance to change direction or keep same direction
% 10 percent chance to change direction
#BeginMacro(getDirection)
if(uniform(0,1) < 0.1, truncUpper(uniform(0,8)), remainder(remainder((0,0),100), 10))
#EndMacro

% Return a new direction
#BeginMacro(changeDirection)
truncUpper(uniform(0,8))
#EndMacro

% Whether the bee will stop to socialize with other bees; Returns boolean
% Stopping power parameter can be either 0.4 or 0.8 and bees have to be present
% Bees have to be present in front of the moving bee (this)
% Select 3 contacts infront of this bee as per [1]
% Ex. Direction = 2 (N), neighbour bees to socialize are at NW, N, and NE
#BeginMacro(socialize)
(uniform(0,1) < 0.8) AND (
  (remainder(remainder((0,0),100), 10) = 2 AND
    ((remainder(remainder((-1,-1),100), 10) >= 1 AND remainder(remainder((-1,-1),100), 10) <= 8) OR
    (remainder(remainder((-1,0),100), 10) >= 1 AND remainder(remainder((-1,0),100), 10) <= 8) OR
    (remainder(remainder((-1,1),100), 10) >= 1 AND remainder(remainder((-1,1),100), 10) <= 8))) OR
  (remainder(remainder((0,0),100), 10) = 3 AND
    ((remainder(remainder((-1,0),100), 10) >= 1 AND remainder(remainder((-1,0),100), 10) <= 8) OR
    (remainder(remainder((-1,1),100), 10) >= 1 AND remainder(remainder((-1,1),100), 10) <= 8) OR
    (remainder(remainder((0,1),100), 10) >= 1 AND remainder(remainder((0,1),100), 10) <= 8))) OR
  (remainder(remainder((0,0),100), 10) = 4 AND
    ((remainder(remainder((-1,1),100), 10) >= 1 AND remainder(remainder((-1,1),100), 10) <= 8) OR
    (remainder(remainder((0,1),100), 10) >= 1 AND remainder(remainder((0,1),100), 10) <= 8) OR
    (remainder(remainder((1,1),100), 10) >= 1 AND remainder(remainder((1,1),100), 10) <= 8))) OR
  (remainder(remainder((0,0),100), 10) = 5 AND
    ((remainder(remainder((0,1),100), 10) >= 1 AND remainder(remainder((0,1),100), 10) <= 8) OR
    (remainder(remainder((1,1),100), 10) >= 1 AND remainder(remainder((1,1),100), 10) <= 8) OR
    (remainder(remainder((1,0),100), 10) >= 1 AND remainder(remainder((1,0),100), 10) <= 8))) OR
  (remainder(remainder((0,0),100), 10) = 6 AND
    ((remainder(remainder((1,1),100), 10) >= 1 AND remainder(remainder((1,1),100), 10) <= 8) OR
    (remainder(remainder((1,0),100), 10) >= 1 AND remainder(remainder((1,0),100), 10) <= 8) OR
    (remainder(remainder((1,-1),100), 10) >= 1 AND remainder(remainder((1,-1),100), 10) <= 8))) OR
  (remainder(remainder((0,0),100), 10) = 7 AND
    ((remainder(remainder((1,0),100), 10) >= 1 AND remainder(remainder((1,0),100), 10) <= 8) OR
    (remainder(remainder((1,-1),100), 10) >= 1 AND remainder(remainder((1,-1),100), 10) <= 8) OR
    (remainder(remainder((0,-1),100), 10) >= 1 AND remainder(remainder((0,-1),100), 10) <= 8))) OR
  (remainder(remainder((0,0),100), 10) = 8 AND
    ((remainder(remainder((1,-1),100), 10) >= 1 AND remainder(remainder((1,-1),100), 10) <= 8) OR
    (remainder(remainder((0,-1),100), 10) >= 1 AND remainder(remainder((0,-1),100), 10) <= 8) OR
    (remainder(remainder((-1,-1),100), 10) >= 1 AND remainder(remainder((-1,-1),100), 10) <= 8))) OR
  (remainder(remainder((0,0),100), 10) = 1 AND
    ((remainder(remainder((0,-1),100), 10) >= 1 AND remainder(remainder((0,-1),100), 10) <= 8) OR
    (remainder(remainder((-1,-1),100), 10) >= 1 AND remainder(remainder((-1,-1),100), 10) <= 8) OR
    (remainder(remainder((-1,0),100), 10) >= 1 AND remainder(remainder((-1,0),100), 10) <= 8)))
)
#EndMacro

% Checks to see if cell the bee is moving to is clear of other bees
% M = 1 in blank cell (D = 0) if bee is moving to it, otherwise it is not clear or another bee is moving there 
#BeginMacro(moveClear)
(remainder(remainder((0,0),100), 10) = 1 AND trunc(remainder((-1,-1),100) / 10) = 1 AND remainder(remainder((-1,-1),100), 10) = 0) OR
(remainder(remainder((0,0),100), 10) = 2 AND trunc(remainder((-1,0),100) / 10) = 1 AND remainder(remainder((-1,0),100), 10) = 0) OR
(remainder(remainder((0,0),100), 10) = 3 AND trunc(remainder((-1,1),100) / 10) = 1 AND remainder(remainder((-1,1),100), 10) = 0) OR
(remainder(remainder((0,0),100), 10) = 4 AND trunc(remainder((0,1),100) / 10) = 1 AND remainder(remainder((0,1),100), 10) = 0) OR
(remainder(remainder((0,0),100), 10) = 5 AND trunc(remainder((1,1),100) / 10) = 1 AND remainder(remainder((1,1),100), 10) = 0) OR
(remainder(remainder((0,0),100), 10) = 6 AND trunc(remainder((1,0),100) / 10) = 1 AND remainder(remainder((1,0),100), 10) = 0) OR
(remainder(remainder((0,0),100), 10) = 7 AND trunc(remainder((1,-1),100) / 10) = 1 AND remainder(remainder((1,-1),100), 10) = 0) OR
(remainder(remainder((0,0),100), 10) = 8 AND trunc(remainder((0,-1),100) / 10) = 1 AND remainder(remainder((0,-1),100), 10) = 0)
#EndMacro