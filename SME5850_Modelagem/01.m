v1 = [1 2 3 4 5];
v2 = [6 7 8 9 10];

qa = v1 * v2';
qb = v1' * v2;
qc = v1 .* v2;
qd = v1 * v1';
qe = v1 .^ 2;
qf = v1 .* v1;