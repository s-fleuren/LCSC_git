hold off;
hold on;
filename = 'outputplot001.txt';
delimiterIn = ' ';
headerlinesIn = 0;
A = importdata(filename,delimiterIn,headerlinesIn);
ax1 = subplot(2,2,1);
plot(A(1:11, 1), A(1:11, 2), A(12:22, 1), A(12:22, 2),... 
A(23 : 33, 1), A(23:33, 2), A(34 : 44, 1), A(34:44, 2));
xticks(ax1,[0 : 60 : 600])
ylim([-inf 50])
grid on
legend({'$f_t$', '$g_{\delta}$', '$f_{\delta_W}$', '$g_{\delta_W}$'},... 
'Interpreter', 'latex', 'Location', 'SouthEast');
title(ax1,'$m = 20$, $p_m = 0.001$', 'Interpreter', 'latex');

filename = 'outputplot011.txt';
delimiterIn = ' ';
headerlinesIn = 0;
A = importdata(filename,delimiterIn,headerlinesIn);
ax2 = subplot(2,2,2);
plot(A(1:11, 1), A(1:11, 2), A(12:22, 1), A(12:22, 2),... 
A(23 : 33, 1), A(23:33, 2), A(34 : 44, 1), A(34:44, 2));
xticks(ax2,[0 : 60 : 600]);
ylim([-inf 50])
grid on
legend({'$f_t$', '$g_{\delta}$', '$f_{\delta_W}$', '$g_{\delta_W}$'},... 
'Interpreter', 'latex', 'Location', 'SouthEast');
title(ax2,'$m = 80$, $p_m = 0.001$', 'Interpreter', 'latex');

filename = 'outputplot101.txt';
delimiterIn = ' ';
headerlinesIn = 0;
A = importdata(filename,delimiterIn,headerlinesIn);
ax3 = subplot(2,2,3);
plot(A(1:11, 1), A(1:11, 2), A(12:22, 1), A(12:22, 2),... 
A(23 : 33, 1), A(23:33, 2), A(34 : 44, 1), A(34:44, 2));
xticks(ax3,[0 : 60 : 600]);
ylim([-inf 50])
grid on
legend({'$f_t$', '$g_{\delta}$', '$f_{\delta_W}$', '$g_{\delta_W}$'},... 
'Interpreter', 'latex', 'Location', 'SouthEast');
title(ax3,'$m = 20$, $p_m = 0.1$', 'Interpreter', 'latex');

filename = 'outputplot111.txt';
delimiterIn = ' ';
headerlinesIn = 0;
A = importdata(filename,delimiterIn,headerlinesIn);
ax4 = subplot(2,2,4);
plot(A(1:11, 1), A(1:11, 2), A(12:22, 1), A(12:22, 2),... 
A(23 : 33, 1), A(23:33, 2), A(34 : 44, 1), A(34:44, 2));
xticks(ax4,[0 : 60 : 600]);
ylim([-inf 50])
grid on
legend({'$f_t$', '$g_{\delta}$', '$f_{\delta_W}$', '$g_{\delta_W}$'},... 
'Interpreter', 'latex', 'Location', 'SouthEast');
title(ax4,'$m = 80$, $p_m = 0.1$', 'Interpreter', 'latex');

