硬件连接：
		Rx 和 Tx直连(PA10和PA9连接)
		
软件代码：
		采用循环间隔1s发送一次
		中断接受数据，接受之后将LED标志位led_flag取反，
		主函数中根据led_flag来点亮led
		
现象：LED闪烁间隔为1s
	