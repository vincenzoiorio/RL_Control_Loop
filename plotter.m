% Specify the filename of the text file to read
filename = 'output.txt';

% Read the data from the text file
data = dlmread(filename);

% Calculate the time points for each row (assuming 10 ms intervals)
t = 0 : 0.01 : (size(data, 1)-1)*0.01;

% Extract the x and y data from the columns of the matrix
x = data(:,1);
y = data(:,2);

% Create a time series plot of the data
plot(t, x, t, y);

% Add a title and axis labels to the plot
title('Time Series Plot of Data');
xlabel('Time (s)');
ylabel('Value');
legend('State of System', 'Control action');