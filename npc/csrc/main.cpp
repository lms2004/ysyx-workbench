#include <verilated.h>
#include <verilated_vcd_c.h>  // 波形跟踪需要
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Vexample.h"  // 注意根据你的顶层模块命名

#define MAX_SIM_TIME 100  // 最大仿真时钟周期
vluint64_t sim_time = 0;  // 仿真周期计数

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Vexample* top = new Vexample;  // 创建顶层模块实例

    // 启用波形跟踪
    Verilated::traceEverOn(true);  // 固定的波形跟踪启用代码
    VerilatedVcdC* m_trace = new VerilatedVcdC;
    top->trace(m_trace, 5);  // 设置波形跟踪深度
    m_trace->open("waveform.vcd");  // 打开vcd文件，用于记录波形

    // 仿真循环
    while (sim_time < MAX_SIM_TIME) {
        int a = rand() & 1;
        int b = rand() & 1;
        top->a = a;         // 设置输入端口 a
        top->b = b;         // 设置输入端口 b
        top->eval();        // 计算输出

        assert(top->f == (a ^ b));

        m_trace->dump(sim_time);  // 记录当前状态到波形
        sim_time++;  // 增加仿真时间
    }

    // 结束处理
    m_trace->close();

    delete m_trace;  // 删除波形文件实例
    return 0;
}
