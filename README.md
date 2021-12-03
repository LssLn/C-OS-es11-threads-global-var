# C-OS-es11-threads-global-var
Main thread genera thread a, hanno in comune la var globale count, inizializzata a 0. Ad un certo punto il main gli da un valore , alchè il thread secondario, in attesa che count sia diversa da 0, gli aggiunge 10 e poi finisce. Main thread aspetta il thread secondario
