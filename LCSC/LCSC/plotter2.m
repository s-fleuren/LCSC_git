hold off;
hold on;
filename1 = 'outputplot004.txt';
filename2 = 'outputplot014.txt';
filename3 = 'outputplot104.txt';
filename4 = 'outputplot114.txt';
max = 60;
delimiterIn = ' ';
headerlinesIn = 0;
A = importdata(filename1,delimiterIn,headerlinesIn);
B = importdata(filename2,delimiterIn,headerlinesIn);
C = importdata(filename3,delimiterIn,headerlinesIn);
D = importdata(filename4,delimiterIn,headerlinesIn);
x = 0;
ax1 = subplot(2,2,1);
plot(A((x + 1):(x + 11), 1), A((x + 1):(x + 11), 2),...
    B((x + 1):(x + 11), 1), B((x + 1):(x + 11), 2),... 
    C((x + 1):(x + 11), 1), C((x + 1):(x + 11), 2),...
    D((x + 1):(x + 11), 1), D((x + 1):(x + 11), 2));
xticks(ax1,[0 : 60 : 600])
ylim([-inf max])
grid on
legend({'$m=20, p_m = 0.001$', '$m = 80, p_m = 0.001$',...
    '$m = 20, p_m = 0.1$', '$m = 80, p_m = 0.1$'},... 
'Interpreter', 'latex', 'Location', 'SouthEast');
title(ax1,'$f_t$', 'Interpreter', 'latex');

x = 11;
ax2 = subplot(2,2,2);
plot(A((x + 1):(x + 11), 1), A((x + 1):(x + 11), 2),...
    B((x + 1):(x + 11), 1), B((x + 1):(x + 11), 2),... 
    C((x + 1):(x + 11), 1), C((x + 1):(x + 11), 2),...
    D((x + 1):(x + 11), 1), D((x + 1):(x + 11), 2));
xticks(ax2,[0 : 60 : 600]);
ylim([-inf max])
grid on
legend({'$m=20, p_m = 0.001$', '$m = 80, p_m = 0.001$',...
    '$m = 20, p_m = 0.1$', '$m = 80, p_m = 0.1$'},... 
'Interpreter', 'latex', 'Location', 'SouthEast');
title(ax2,'$g_\delta$', 'Interpreter', 'latex');

x = 22;
ax3 = subplot(2,2,3);
plot(A((x + 1):(x + 11), 1), A((x + 1):(x + 11), 2),...
    B((x + 1):(x + 11), 1), B((x + 1):(x + 11), 2),... 
    C((x + 1):(x + 11), 1), C((x + 1):(x + 11), 2),...
    D((x + 1):(x + 11), 1), D((x + 1):(x + 11), 2));
xticks(ax3,[0 : 60 : 600]);
ylim([-inf max])
grid on
legend({'$m=20, p_m = 0.001$', '$m = 80, p_m = 0.001$',...
    '$m = 20, p_m = 0.1$', '$m = 80, p_m = 0.1$'},... 
'Interpreter', 'latex', 'Location', 'SouthEast');
title(ax3,'$f_{\delta_W}$', 'Interpreter', 'latex');

x = 33;
ax4 = subplot(2,2,4);
plot(A((x + 1):(x + 11), 1), A((x + 1):(x + 11), 2),...
    B((x + 1):(x + 11), 1), B((x + 1):(x + 11), 2),... 
    C((x + 1):(x + 11), 1), C((x + 1):(x + 11), 2),...
    D((x + 1):(x + 11), 1), D((x + 1):(x + 11), 2));
xticks(ax4,[0 : 60 : 600]);
ylim([-inf max])
grid on
legend({'$m=20, p_m = 0.001$', '$m = 80, p_m = 0.001$',...
    '$m = 20, p_m = 0.1$', '$m = 80, p_m = 0.1$'},... 
'Interpreter', 'latex', 'Location', 'SouthEast');
title(ax4,'$g_{\delta_W}$', 'Interpreter', 'latex');

