% Holds the encoding and decoding of the cell state for the bee and cell beehaviour
% State description:
% ====================
% TTMD - each letter represents a digit, therefore the state is 4 digits
% TT - The ambient temperature of cell, 28 <= TT <= 36 (bounded by [1])
% M  - A state var to keep state of movement across cells (0 - 8)
%      - Bee cell: M holds the movement state of the bee: {0 -> rest, 1 -> change direction, 2 -> move indent, 3 -> moving }
%      - Blank cell: M holds the number of bees that want to move to that cell (max 8)
%      - M is 0 for walls and varies from 1 to 9 depending on CASU output temp
% D  - The direction of the Bee, 1 <= D <= 8, 0 for blank cell and 9 for walls and CASU robots, therefore indication of a bee is if D is between 1 and8
%      Layout:
%      1 2 3
%      8 0 4
%      7 6 5

% Since there are no parameters, need to create decoder for each cell in Moore neighbourhood
% (row, col)
% Origin Decoding (0,0) ==============
#BeginMacro(decodeOOTT)
trunc((0,0) / 100)
#EndMacro

#BeginMacro(decodeOOM)
trunc(remainder((0,0),100) / 10)
#EndMacro

#BeginMacro(decodeOOD)
remainder(remainder((0,0),100), 10)
#EndMacro

% North Decoding (-1,0) ================
#BeginMacro(decodeNNTT)
trunc((-1,0) / 100)
#EndMacro

#BeginMacro(decodeNNM)
trunc(remainder((-1,0),100) / 10)
#EndMacro

#BeginMacro(decodeNND)
remainder(remainder((-1,0),100), 10)
#EndMacro

% East Decoding (0,1) ================
#BeginMacro(decodeEETT)
trunc((0,1) / 100)
#EndMacro

#BeginMacro(decodeEEM)
trunc(remainder((0,1),100) / 10)
#EndMacro

#BeginMacro(decodeEED)
remainder(remainder((0,1),100), 10)
#EndMacro

% South Decoding (1,0) ================
#BeginMacro(decodeSSTT)
trunc((1,0) / 100)
#EndMacro

#BeginMacro(decodeSSM)
trunc(remainder((1,0),100) / 10)
#EndMacro

#BeginMacro(decodeSSD)
remainder(remainder((1,0),100), 10)
#EndMacro

% West Decoding (0,-1) ================
#BeginMacro(decodeWWTT)
trunc((0,-1) / 100)
#EndMacro

#BeginMacro(decodeWWM)
trunc(remainder((0,-1),100) / 10)
#EndMacro

#BeginMacro(decodeWWD)
remainder(remainder((0,-1),100), 10)
#EndMacro

% NW Decoding (-1,-1) ================
#BeginMacro(decodeNWTT)
trunc((-1,-1) / 100)
#EndMacro

#BeginMacro(decodeNWM)
trunc(remainder((-1,-1),100) / 10)
#EndMacro

#BeginMacro(decodeNWD)
remainder(remainder((-1,-1),100), 10)
#EndMacro

% NE Decoding (-1,1) ================
#BeginMacro(decodeNETT)
trunc((-1,1) / 100)
#EndMacro

#BeginMacro(decodeNEM)
trunc(remainder((-1,1),100) / 10)
#EndMacro

#BeginMacro(decodeNED)
remainder(remainder((-1,1),100), 10)
#EndMacro

% SE Decoding (1,1) ================
#BeginMacro(decodeSETT)
trunc((1,1) / 100)
#EndMacro

#BeginMacro(decodeSEM)
trunc(remainder((1,1),100) / 10)
#EndMacro

#BeginMacro(decodeSED)
remainder(remainder((1,1),100), 10)
#EndMacro

% SW Decoding (1,-1) ================
#BeginMacro(decodeSWTT)
trunc((1,-1) / 100)
#EndMacro

#BeginMacro(decodeSWM)
trunc(remainder((1,-1),100) / 10)
#EndMacro

#BeginMacro(decodeSWD)
remainder(remainder((1,-1),100), 10)
#EndMacro

% [1] Governing the Swarm paper