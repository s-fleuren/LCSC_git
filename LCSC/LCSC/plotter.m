hold off;
filename = 'outputplot001.txt';
delimiterIn = ' ';
headerlinesIn = 0;
A = importdata(filename,delimiterIn,headerlinesIn);
plot(A(1:6, 1), A(1:6, 2), A(7:12, 1), A(7:12, 2),... 
A(13 : 18, 1), A(13:18, 2), A(19 : 24, 1), A(19:24, 2));
hold on;
legend({'$f_t$', '$g_{\delta}$', '$f_{\delta_W}$', '$g_{\delta_W}$'},... 
'Interpreter', 'latex', 'Location', 'SouthEast');

