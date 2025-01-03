2024-05-22
SHA-1: bda6d635658a568250e2d3e10f5c6c514d09e55e

2024-06-06
SHA-1: 1872c1396ad7bc7a3763d656d66c3888e701b73a
1. add RGB light demo
2. modify flash layout
3. add an example of manufacturer scene command handler

2024-07-23
SHA-1: 30f0f7834cd7fa07c095078162f73ddd98892a8e
1. update driver for 4M Flash
2. adapt to the new 4M Flash partition

2024-07-29
SHA-1: 9e7a3e5a0a2f32366631bbc07dfca616c76aacb4
1. change debug Pin from PD2 to PB2 on b92 EVK board

2024-08-21
SHA-1: ccc54c59c35073eac7289c220a8c869a06513078
1. fix the aligment issue of structure ikea_moveScene_t
2. update drivers(dcoc calibration, capacitor selection, crystal manual settle)
3. enable gaussian filtering
4. provide token processing demo

2024-09-12
SHA-1: fcd94f501dcc26769652ba0662899792caf5983f
1. remove gaussian filtering

2024-10-12
SHA-1: ee7603746cad698d142763074e9471bcbe1abf51
1. fix touch link issue when not starting BDB steering
2. add samplePlug demo

2024-11-23
SHA-1: 30eef7d52891528f5747b57c158659f1ad8ef75a
1. update sampleLight demo for certification
	note: 1)Only when TEST_FOR_CERTIFICATION is set to 1, the Certification Link Key will be used.
			Therefore, during product certification, it must be defined as 1, while the retail industry defines it as 0.
			In addition, when TEST_FOR_CERTIFICATION is 1, the demo will not jump to Matter.
		  2)OTA and GP are enabled by default.
			Define ZCL_OTA_SUPPORT and ZCL_GP_SUPPORT as 0 to disable OTA and Green Power features, if needed.
		
2024-12-17
SHA-1: 847725c7bcf9f685edc6809f3c237aa977504da2
1. add shell and tools to Linux
2. update demo