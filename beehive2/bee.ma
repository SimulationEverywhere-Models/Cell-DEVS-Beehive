#include(encoding.inc)
#include(cellMacros.inc)

[top]
components : bee

[bee]
type : cell
dim : (50,50)
delay : inertial
defaultDelayTime : 1
border : wrapped
neighbors : bee(-1,-1) bee(-1,0) bee(-1,1)
neighbors : bee(0,-1)  bee(0,0)  bee(0,1)
neighbors : bee(1,-1)  bee(1,0)  bee(1,1)
initialvalue : 2800
initialCellsValue : bee.val
localtransition : bee-rule


[bee-rule]
% Blank Cell Rules ===========================
% Set temp + move indents if no bee is moving in
rule : {(#macro(temp)) * 100 + (#macro(getBlankM)) * 10} 0 {#macro(isBlank) AND #macro(beeMoveD) = 0}
% Move bee into the following blank cell and set M to 1
rule : {(#macro(temp)) * 100 + 10 + #macro(beeMoveD)} 0 {#macro(isBlank) AND #macro(beeMoveD) > 0}
% End Blank Cell Rules =======================

% Bee Cell Rules =============================
% Bee is waiting at M = 0; changing direction at M = 1; checking direction at M = 2, socializing, and broadcasting indent at M = 3, and moving to blank cell at M = 4
rule : {(#macro(temp)) * 100 + (10 + #macro(decodeOOD))} {(#macro(waitTime)) * 1000} {#macro(isBee) AND #macro(decodeOOM) = 0}
rule : {(#macro(temp)) * 100 + 20 + #macro(getDirection)} 0 {#macro(isBee) AND #macro(decodeOOM) = 1}
rule : {(#macro(temp)) * 100 + (if((#macro(moveClear)),30,10)) + (#macro(decodeOOD))} 100 {#macro(isBee) AND #macro(decodeOOM) = 2}
rule : {(#macro(temp)) * 100 + (if((#macro(moveClear)) AND (not (#macro(socialize))),40,0)) + #macro(decodeOOD)} 500 {#macro(isBee) AND #macro(decodeOOM) = 3}
rule : {(#macro(temp)) * 100} 0 {#macro(isBee) AND #macro(decodeOOM) = 4}
% End Bee Cell Rules =========================

% Finally, stay the same if nothing was triggered
rule : {(0,0)} 0 { t }