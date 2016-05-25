%Jogo de caça à raposa.
%Desenvolvido por Matheus Mahl e TCS

%---------------------------------------------------------------------------------------
raposa(raposa1).

%---------------------------------------------------------------------------------------
cao(cao1).
cao(cao2).
cao(cao3).
cao(cao4).

%---------------------------------------------------------------------------------------
%Locais possiveis no tabuleiro
local(1,1).
local(3,1).
local(5,1).
local(7,1).
local(2,2).
local(4,2).
local(6,2).
local(8,2).
local(1,3).
local(3,3).
local(5,3).
local(7,3).
local(2,4).
local(4,4).
local(6,4).
local(8,4).
local(1,5).
local(3,5).
local(5,5).
local(7,5).
local(2,6).
local(4,6).
local(6,6).
local(8,6).
local(1,7).
local(3,7).
local(5,7).
local(7,7).
local(2,8).
local(4,8).
local(6,8).
local(8,8).
%---------------------------------------------------------------------------------------
%X e Y são os locais atuais, A e B são os novos locais
local_vizinho(X,Y,A,B) :- validar_direita(X,Y,A,B),!; validar_esquerda(X,Y,A,B), !.

validar_direita(X,Y,A,B) :- ((X+1) =:= A), ((Y+1) =:= B), !.

validar_esquerda(X,Y,A,B) :- ((X-1) =:= A), ((Y+1) =:= B), !.
%---------------------------------------------------------------------------------------
%Guarda dinamicamente a posicao dos cães.

:- dynamic posicao_cao/2.

posicao_cao(cao1, local(1,1)).
posicao_cao(cao2, local(3,1)).
posicao_cao(cao3, local(5,1)).
posicao_cao(cao4, local(7,1)).

%---------------------------------------------------------------------------------------
%Guarda dinamicamente a posicao da raposa.

:- dynamic posicao_raposa/2.

posicao_raposa(raposa1, local(4,8)).

%---------------------------------------------------------------------------------------
%Escreve a posicao dos caes e da raposa.

escrever_posicoes_caes :- posicao_cao(Cao, Posicao), write(Cao), write('-->'), write(Posicao).
escrever_posicao_raposa :- posicao_raposa(Raposa, Posicao), write(Raposa), write('-->'), write(Posicao).

escrever_posicoes_todos :- escrever_posicoes_caes; escrever_posicao_raposa.

%---------------------------------------------------------------------------------------

%Valida a movimentação
%Realiza o movimento do Cao
%Chama a função para movimentar a raposa.

movimentar(Cao,X,Y) :- validar_movimento(Cao,X,Y), retractall(posicao_cao(Cao,_)),assert(posicao_cao(Cao, local(X,Y))), movimentar_raposa, !.

%---------------------------------------------------------------------------------------

%Valida se o local existe, valida se o local é valido,
%Valida se o cao não está naquele local, valida se não tem outro cao naquele local
%Valida se a raposa não está naquele local
validar_movimento(Cao, X, Y) :- local(X,Y), posicao_cao(Cao, local(F,G)), local_vizinho(F,G,X,Y), 
	not(posicao_cao(_, local(X,Y))), not(posicao_raposa(_, local(X,Y))), !.

%---------------------------------------------------------------------------------------

%Reinicia a posicao das peças.
inicio :- retractall(posicao_cao(_,_)), assert(posicao_cao(cao1,local(1,1))),assert(posicao_cao(cao2,local(3,1))), assert(posicao_cao(cao3,local(5,1))),
assert(posicao_cao(cao4,local(7,1))), retractall(posicao_raposa(_,_)), assert(posicao_raposa(raposa1,local(4,8))), !.

%---------------------------------------------------------------------------------------

%Valida se a posicão é possivel
validar_movimento_raposa(PosX, PosY) :- local(PosX, PosY), not(posicao_cao(_, local(PosX, PosY))), !.
%write('|PosX:'), write(PosX), write('|PosY:'), write(PosY),

%---------------------------------------------------------------------------------------
%Retorna nova posicao da raposa %Fazer o retorno já válido!!!!

retornar_posicao_nova(X, Y, PosicaoX, PosicaoY) :- retornar_Y(X, Y, PosicaoY), retornar_X(X, PosicaoY, PosicaoX), !.

%---------------------------------------------------------------------------------------
retornar_Y(X, Y, Pos_Poss_Y) :-
PosX is X - 1, Pos_Poss_Y is Y - 1, validar_movimento_raposa(PosX, Pos_Poss_Y), !; % write('|1 Pos_Poss_Y:'), write(Pos_Poss_Y), !;
PosX is X + 1, Pos_Poss_Y is Y - 1, validar_movimento_raposa(PosX, Pos_Poss_Y), !; % write('|2 Pos_Poss_Y:'), write(Pos_Poss_Y), !;
PosX is X - 1, Pos_Poss_Y is Y + 1, validar_movimento_raposa(PosX, Pos_Poss_Y), !; % write('|3 Pos_Poss_Y:'), write(Pos_Poss_Y), !;
PosX is X + 1, Pos_Poss_Y is Y + 1, validar_movimento_raposa(PosX, Pos_Poss_Y), !; % write('|4 Pos_Poss_Y:'), write(Pos_Poss_Y), !;
write('A raposa está encurralada!'), fail,!.

%---------------------------------------------------------------------------------------

retornar_X(X, Y, Pos_Poss_X) :-
	random_between(0, 1, A), (A =:= 1 -> Pos_Poss_X is X + 1; Pos_Poss_X is X - 1), validar_movimento_raposa(Pos_Poss_X, Y), !;
	Pos_Poss_X is X - 1, validar_movimento_raposa(Pos_Poss_X, Y), !;
	Pos_Poss_X is X + 1, validar_movimento_raposa(Pos_Poss_X, Y), !.

%---------------------------------------------------------------------------------------

movimentar_raposa :- posicao_raposa(raposa1, local(X,Y)), retornar_posicao_nova(X,Y, PosicaoX, PosicaoY), 
	write('|Posicao Raposa X: '),
	write(PosicaoX),
	write(' |Posicao Raposa Y: '),
	write(PosicaoY),
	retractall(posicao_raposa(raposa1,_)), assert(posicao_raposa(raposa1, local(PosicaoX, PosicaoY))), !.

%---------------------------------------------------------------------------------------