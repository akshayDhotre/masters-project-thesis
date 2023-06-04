/* code to implement feedback via aproximate linearization */
#include<stdio.h>
#include<math.h>

#define STATE_VECTOR_SIZE 4
#define NUM_STATES 10

struct state {
	float x;
	float y;
	float theta;
	float phi;
	float u1;
	float u2;
};

const int AMPLITUDE = 1;
const int WN = 5;
const int LAMB_1 = 5;
const int LAMB_2 = 5;
const int ZETA = 1;
const float W = 3.1427;
const int TS = 1;	/* Sampling time is 1 second */


void FB_approx_lin(struct state desired_st[NUM_STATES])
{
    float u1_err, u2_err;
    float u1_err_tminus1, u2_err_tminus1;
    float u_err_matrix[2][1];


    float K1 = LAMB_1;
    float K2 = LAMB_2 + (2 * ZETA * WN);
    float K3 = pow(WN, 2) + (2 * ZETA * WN * LAMB_2);
    float K4 = pow(WN, 2) * LAMB_2;

    float A[4][4] = {   {0, 0, 0, 0}, 
			{0, 0, 0, 0}, 
			{0, 0, 0, 0}, /* 2, 1 is to be replaced by x_desired.u1 */
			{0, 0, 0, 0} }; /* 3, 2 is to be replaced by x_desired.u1 */

    float B[4][2] = {   {1, 0}, 
			{0, 1}, 
			{0, 0}, /* 2, 0 to be replaced by x_desired.y */
			{0, 0} };	/* 3, 0 to be replaced by x_desired.theta */

    float term1[4][1];
    float term2[4][1];

    /* default values assumed for 0th iteration */
    struct state x_desired = {0, 0, (AMPLITUDE * W), 0};
    struct state x_actual = {-2, 0, (AMPLITUDE * W), -1};
    struct state x_err;
    float x_err_matrix[4][1];

    x_err.x = x_desired.x - x_actual.x;
    x_err.y = x_desired.y - x_actual.y;
    x_err.theta = x_desired.theta - x_actual.theta;
    x_err.phi = x_desired.phi - x_actual.phi;

    /* Error model */
    for (int t = 0; t < NUM_STATES; t++) {
	u1_err = -(K1 * x_err.x);
	u2_err = -(K2 * x_err.y) - ((K3 / x_desired.u1) * x_err.theta) - \
	    	((K4 / pow(x_desired.u1, 2)) * x_err.phi);

	x_actual.u1 = x_desired.u1 + u1_err;
       	x_actual.u2 = x_desired.u2 + u2_err;
       
	/* Pass u1, u2 values to the plant */

	/* Now get actual values from sensors */
	/* x_actual = { values from sensor }; */

	/* Get desired X */
	x_desired = desired_st[t + 1];

	/* Calculate xerror for this time instant */
	x_err.x = x_desired.x - x_actual.x;
	x_err.y = x_desired.y - x_actual.y;
	x_err.theta = x_desired.theta - x_actual.theta;
	x_err.phi = x_desired.phi - x_actual.phi;

	/* Update matrix A*/
	A[2][1] = x_desired.u1;
	A[3][2] = x_desired.u1;
	
	/* Update matrix B */
	B[2][0] = x_desired.y;
	B[3][0] = x_desired.theta;

	/* A * x_err */
       	x_err_matrix[0][0] = x_err.x;
       	x_err_matrix[1][0] = x_err.y;
       	x_err_matrix[2][0] = x_err.theta;
       	x_err_matrix[3][0] = x_err.phi;

	int m1_rows = 4;
	int m1_cols = 4;
	int m2_rows = 4;
	int m2_cols = 1;

	float sum = 0;
	for (int c = 0; c < m1_rows; c++) {
		for (int d = 0; d < m2_cols; d++) {
			for (int k = 0; k < m2_rows; k++) {
				sum += (A[c][k] * x_err_matrix[k][d]);
			}
			term1[c][d] = sum;
			sum = 0;
		}
	}


	/* B * u_error */
	u_err_matrix[0][0] = u1_err;
	u_err_matrix[1][0] = u2_err;

	m1_rows = 4;
	m1_cols = 2;
	m2_rows = 2;
	m2_cols = 1;

	sum = 0;
	for (int c = 0; c < m1_rows; c++) {
		for (int d = 0; d < m2_cols; d++) {
			for (int k = 0; k < m2_rows; k++) {
				sum += (B[c][k] * u_err_matrix[k][d]);
			}
			term2[c][d] = sum;
			sum = 0;
		}
	}
	
	/* Add matrices term1 and term2 */
	for (int i = 0; i < m1_rows; i++) {
		for (int j = 0; j < m2_cols; j++) {
			x_err_matrix[i][0] = x_err_matrix[i][0] + ((term1[i][j] + term2[i][j]) * TS);
		}
	}
	/* x_err_matrix now has X error t + 1 */
	x_err.x 	=  x_err_matrix[1][0];
	x_err.y 	=  x_err_matrix[2][0];
	x_err.theta 	=  x_err_matrix[3][0];
	x_err.phi 	=  x_err_matrix[4][0];
    }	/* end of states loop */
}


void main()
{
	struct state desired_st[NUM_STATES];

	/* for the time-being, hard code desired state values */
	for (int t = 0; t < NUM_STATES; t++) {
		desired_st[t].x = t;
		desired_st[t].y = AMPLITUDE * sin(W * t);
		desired_st[t].theta = 1;
		desired_st[t].phi = -AMPLITUDE * pow(W, 3) * cos(W * t);
		desired_st[t].u1 = 1;
		desired_st[t].u2 = - AMPLITUDE * pow(W, 3);
	}

	FB_approx_lin(desired_st);
}
