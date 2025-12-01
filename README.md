<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>STM32 I2C LCD Library | HD44780 with PCF8574</title>
    <style>
        :root {
            --primary: #0066cc;
            --primary-dark: #004d99;
            --secondary: #00a8ff;
            --accent: #00d2ff;
            --light: #f8f9fa;
            --dark: #212529;
            --success: #28a745;
            --gray: #6c757d;
            --border-radius: 8px;
            --shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
            --transition: all 0.3s ease;
        }

        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }

        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            line-height: 1.6;
            color: var(--dark);
            background-color: #f5f7fa;
        }

        .container {
            max-width: 1200px;
            margin: 0 auto;
            padding: 0 20px;
        }

        header {
            background: linear-gradient(135deg, var(--primary), var(--secondary));
            color: white;
            padding: 2rem 0;
            text-align: center;
            box-shadow: var(--shadow);
        }

        .logo {
            font-size: 2.5rem;
            margin-bottom: 0.5rem;
        }

        .tagline {
            font-size: 1.2rem;
            opacity: 0.9;
            margin-bottom: 1rem;
        }

        .badges {
            display: flex;
            justify-content: center;
            gap: 10px;
            flex-wrap: wrap;
            margin-top: 1rem;
        }

        .badge {
            background: rgba(255, 255, 255, 0.2);
            padding: 5px 12px;
            border-radius: 20px;
            font-size: 0.85rem;
            display: inline-flex;
            align-items: center;
            gap: 5px;
        }

        .badge i {
            font-size: 1rem;
        }

        main {
            padding: 2rem 0;
        }

        section {
            background: white;
            border-radius: var(--border-radius);
            box-shadow: var(--shadow);
            padding: 2rem;
            margin-bottom: 2rem;
        }

        h1, h2, h3 {
            color: var(--primary);
            margin-bottom: 1rem;
        }

        h2 {
            border-bottom: 2px solid var(--light);
            padding-bottom: 0.5rem;
            margin-bottom: 1.5rem;
        }

        .features-grid {
            display: grid;
            grid-template-columns: repeat(auto-fill, minmax(300px, 1fr));
            gap: 1.5rem;
            margin-top: 1.5rem;
        }

        .feature-card {
            background: var(--light);
            border-radius: var(--border-radius);
            padding: 1.5rem;
            transition: var(--transition);
            border-left: 4px solid var(--success);
        }

        .feature-card:hover {
            transform: translateY(-5px);
            box-shadow: 0 10px 15px rgba(0, 0, 0, 0.1);
        }

        .feature-card h3 {
            display: flex;
            align-items: center;
            gap: 10px;
            margin-bottom: 0.5rem;
        }

        .feature-card i {
            color: var(--success);
        }

        .code-block {
            background: #2d2d2d;
            color: #f8f8f2;
            border-radius: var(--border-radius);
            padding: 1.5rem;
            margin: 1.5rem 0;
            overflow-x: auto;
            font-family: 'Courier New', Courier, monospace;
        }

        .code-comment {
            color: #75715e;
        }

        .code-keyword {
            color: #66d9ef;
        }

        .code-function {
            color: #a6e22e;
        }

        .code-string {
            color: #e6db74;
        }

        .code-number {
            color: #ae81ff;
        }

        .setup-steps {
            counter-reset: step-counter;
            margin: 1.5rem 0;
        }

        .step {
            display: flex;
            margin-bottom: 1.5rem;
            align-items: flex-start;
        }

        .step-number {
            background: var(--primary);
            color: white;
            width: 30px;
            height: 30px;
            border-radius: 50%;
            display: flex;
            align-items: center;
            justify-content: center;
            margin-right: 1rem;
            flex-shrink: 0;
        }

        .step-content {
            flex: 1;
        }

        .chip {
            display: inline-block;
            background: var(--light);
            padding: 5px 10px;
            border-radius: 20px;
            font-size: 0.85rem;
            margin: 0 5px 5px 0;
            border: 1px solid #dee2e6;
        }

        .chip.primary {
            background: var(--primary);
            color: white;
        }

        .btn {
            display: inline-block;
            background: var(--primary);
            color: white;
            padding: 10px 20px;
            border-radius: var(--border-radius);
            text-decoration: none;
            font-weight: 600;
            transition: var(--transition);
            border: none;
            cursor: pointer;
        }

        .btn:hover {
            background: var(--primary-dark);
            transform: translateY(-2px);
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2);
        }

        .btn-secondary {
            background: var(--secondary);
        }

        .btn-secondary:hover {
            background: #0097e6;
        }

        .btn-group {
            display: flex;
            gap: 10px;
            margin-top: 1rem;
            flex-wrap: wrap;
        }

        footer {
            background: var(--dark);
            color: white;
            text-align: center;
            padding: 2rem 0;
            margin-top: 2rem;
        }

        .license {
            margin-top: 1rem;
            opacity: 0.8;
        }

        @media (max-width: 768px) {
            .features-grid {
                grid-template-columns: 1fr;
            }
            
            .btn-group {
                flex-direction: column;
            }
            
            .btn {
                width: 100%;
                text-align: center;
            }
        }
    </style>
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.4.0/css/all.min.css">
</head>
<body>
    <header>
        <div class="container">
            <div class="logo">
                <i class="fas fa-microchip"></i> STM32 I2C LCD Library
            </div>
            <p class="tagline">Lightweight HAL-based library for HD44780 LCD with I2C backpack</p>
            <div class="badges">
                <div class="badge"><i class="fas fa-check-circle"></i> HAL-Based</div>
                <div class="badge"><i class="fas fa-check-circle"></i> Cross-Platform</div>
                <div class="badge"><i class="fas fa-check-circle"></i> MIT Licensed</div>
            </div>
        </div>
    </header>

    <main class="container">
        <section id="overview">
            <h2>Overview</h2>
            <p>A lightweight and portable library to interface HD44780-compatible LCD modules using an I2C backpack (PCF8574) with STM32 microcontrollers. It is written using the STM32 HAL library and is designed to work across STM32 L4, F4, F1, and other series by simply changing the included device header.</p>
            
            <div class="btn-group">
                <a href="#features" class="btn"><i class="fas fa-star"></i> Features</a>
                <a href="#getting-started" class="btn btn-secondary"><i class="fas fa-rocket"></i> Getting Started</a>
                <a href="#api" class="btn"><i class="fas fa-code"></i> API Reference</a>
            </div>
        </section>

        <section id="features">
            <h2><i class="fas fa-check-circle"></i> Features</h2>
            <div class="features-grid">
                <div class="feature-card">
                    <h3><i class="fas fa-microchip"></i> 4-Bit Mode</h3>
                    <p>LCD communication via I2C (PCF8574) using efficient 4-bit mode, reducing pin requirements.</p>
                </div>
                <div class="feature-card">
                    <h3><i class="fas fa-display"></i> Display Compatibility</h3>
                    <p>Works with 16x2, 20x4, and other HD44780-compatible LCD modules.</p>
                </div>
                <div class="feature-card">
                    <h3><i class="fas fa-terminal"></i> Simple API</h3>
                    <p>Easy-to-use functions for printing text, setting cursor position, and controlling the display.</p>
                </div>
                <div class="feature-card">
                    <h3><i class="fas fa-layer-group"></i> HAL Abstraction</h3>
                    <p>Clean abstraction using STM32 HAL I2C for maximum compatibility.</p>
                </div>
                <div class="feature-card">
                    <h3><i class="fas fa-exchange-alt"></i> Cross-Platform</h3>
                    <p>Easily portable to any STM32 series (L4, F4, F1, etc.) with minimal changes.</p>
                </div>
                <div class="feature-card">
                    <h3><i class="fas fa-feather"></i> Lightweight</h3>
                    <p>Minimal dependencies and optimized for resource-constrained environments.</p>
                </div>
            </div>
        </section>

        <section id="getting-started">
            <h2><i class="fas fa-rocket"></i> Getting Started</h2>
            
            <h3>Prerequisites</h3>
            <div class="chips">
                <span class="chip primary">STM32CubeIDE / STM32CubeMX</span>
                <span class="chip">Configured I2C peripheral (e.g., I2C1)</span>
                <span class="chip">LCD I2C backpack (PCF8574 at 0x27 or 0x3F)</span>
            </div>
            
            <h3>Setup</h3>
            <div class="setup-steps">
                <div class="step">
                    <div class="step-number">1</div>
                    <div class="step-content">
                        <p><strong>Clone or copy the library files</strong> into your STM32 project.</p>
                        <div class="code-block">
                            <span class="code-comment">// Add these files to your project:</span><br>
                            lcd_i2c_hal.c<br>
                            lcd_i2c_hal.h
                        </div>
                    </div>
                </div>
                <div class="step">
                    <div class="step-number">2</div>
                    <div class="step-content">
                        <p><strong>Include the header</strong> in your main.c file.</p>
                        <div class="code-block">
                            <span class="code-comment">// In main.c</span><br>
                            <span class="code-keyword">#include</span> <span class="code-string">"lcd_i2c_hal.h"</span>
                        </div>
                    </div>
                </div>
                <div class="step">
                    <div class="step-number">3</div>
                    <div class="step-content">
                        <p><strong>Configure I2C peripheral</strong> using CubeMX (e.g., hi2c1).</p>
                        <div class="code-block">
                            <span class="code-comment">// Ensure I2C is properly initialized</span><br>
                            MX_I2C1_Init(); <span class="code-comment">// Generated by CubeMX</span>
                        </div>
                    </div>
                </div>
            </div>
        </section>

        <section id="api">
            <h2><i class="fas fa-code"></i> Basic Usage Example</h2>
            <div class="code-block">
                <span class="code-comment">// Include the library</span><br>
                <span class="code-keyword">#include</span> <span class="code-string">"lcd_i2c_hal.h"</span><br>
                <br>
                <span class="code-comment">// External I2C handle (defined in main.c)</span><br>
                <span class="code-keyword">extern</span> I2C_HandleTypeDef hi2c1;<br>
                <br>
                <span class="code-comment">// Initialize LCD (I2C address 0x27, 16 columns, 2 rows)</span><br>
                LCD_HandleTypeDef lcd;<br>
                LCD_I2C_Init(&lcd, &hi2c1, 0x27, 16, 2);<br>
                <br>
                <span class="code-comment">// Print text</span><br>
                LCD_I2C_Print(&lcd, <span class="code-string">"Hello, STM32!"</span>);<br>
                <br>
                <span class="code-comment">// Set cursor to second line</span><br>
                LCD_I2C_SetCursor(&lcd, 0, 1);<br>
                LCD_I2C_Print(&lcd, <span class="code-string">"I2C LCD Demo"</span>);<br>
                <br>
                <span class="code-comment">// Clear display</span><br>
                LCD_I2C_Clear(&lcd);<br>
            </div>
        </section>

        <section id="license">
            <h2><i class="fas fa-file-contract"></i> License</h2>
            <p>This project is open-source under the <strong>MIT License</strong>.</p>
            <p>You are free to use, modify, and distribute this software in both commercial and personal projects.</p>
            <div class="code-block">
                <span class="code-comment">/*</span><br>
                <span class="code-comment"> * MIT License</span><br>
                <span class="code-comment"> * </span><br>
                <span class="code-comment"> * Copyright (c) 2024 Your Name</span><br>
                <span class="code-comment"> * </span><br>
                <span class="code-comment"> * Permission is hereby granted, free of charge, to any person obtaining a copy</span><br>
                <span class="code-comment"> * of this software and associated documentation files (the "Software"), to deal</span><br>
                <span class="code-comment"> * in the Software without restriction, including without limitation the rights</span><br>
                <span class="code-comment"> * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell</span><br>
                <span class="code-comment"> * copies of the Software, and to permit persons to whom the Software is</span><br>
                <span class="code-comment"> * furnished to do so, subject to the following conditions:</span><br>
                <span class="code-comment"> * </span><br>
                <span class="code-comment"> * The above copyright notice and this permission notice shall be included in all</span><br>
                <span class="code-comment"> * copies or substantial portions of the Software.</span><br>
                <span class="code-comment"> * </span><br>
                <span class="code-comment"> * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR</span><br>
                <span class="code-comment"> * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,</span><br>
                <span class="code-comment"> * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE</span><br>
                <span class="code-comment"> * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER</span><br>
                <span class="code-comment"> * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,</span><br>
                <span class="code-comment"> * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE</span><br>
                <span class="code-comment"> * SOFTWARE.</span><br>
                <span class="code-comment"> */</span>
            </div>
        </section>
    </main>

    <footer>
        <div class="container">
            <p>STM32 I2C LCD Library - HD44780 with PCF8574 Backpack</p>
            <p class="license">Open source under MIT License</p>
        </div>
    </footer>
</body>
</html>
