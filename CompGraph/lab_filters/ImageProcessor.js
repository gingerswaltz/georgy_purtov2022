class ImageProcessor {
    constructor(imageData) {
        this.imageData = imageData;
        this.width = imageData.width;
        this.height = imageData.height;
    }

    // Функция для применения матрицы свёртки к изображению
    applyConvolution(kernel) {
        const outputData = new Uint8ClampedArray(this.width * this.height * 4);
        const halfKernelSize = Math.floor(kernel.length / 2);

        for (let y = 0; y < this.height; y++) {
            for (let x = 0; x < this.width; x++) {
                let r = 0, g = 0, b = 0;
                for (let i = 0; i < kernel.length; i++) {
                    for (let j = 0; j < kernel.length; j++) {
                        const pixelX = x + j - halfKernelSize;
                        const pixelY = y + i - halfKernelSize;
                        if (pixelX >= 0 && pixelX < this.width && pixelY >= 0 && pixelY < this.height) {
                            const index = (pixelY * this.width + pixelX) * 4;
                            const weight = kernel[i][j];
                            r += this.imageData.data[index] * weight;
                            g += this.imageData.data[index + 1] * weight;
                            b += this.imageData.data[index + 2] * weight;
                        }
                    }
                }
                const currentIndex = (y * this.width + x) * 4;
                outputData[currentIndex] = this.clamp(r);
                outputData[currentIndex + 1] = this.clamp(g);
                outputData[currentIndex + 2] = this.clamp(b);
                outputData[currentIndex + 3] = this.imageData.data[currentIndex + 3];
            }
        }

        return new ImageData(outputData, this.width, this.height);
    }

    // Функция для ограничения значений каналов цвета в пределах от 0 до 255
    clamp(value) {
        return Math.max(0, Math.min(Math.round(value), 255));
    }
}
