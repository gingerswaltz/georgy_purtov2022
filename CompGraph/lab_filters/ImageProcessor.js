class ConvolutionFilter {
    constructor(kernel) {
        this.kernel = kernel;
    }

    apply(imageData) {
        const width = imageData.width;
        const height = imageData.height;
        const data = imageData.data;
        const outputData = new Uint8ClampedArray(data.length);

        const kernelSize = Math.sqrt(this.kernel.length);
        const halfKernelSize = Math.floor(kernelSize / 2);

        for (let y = 0; y < height; y++) {
            for (let x = 0; x < width; x++) {
                let sumR = 0, sumG = 0, sumB = 0;
                for (let ky = 0; ky < kernelSize; ky++) {
                    for (let kx = 0; kx < kernelSize; kx++) {
                        const imgX = x + kx - halfKernelSize;
                        const imgY = y + ky - halfKernelSize;
                        if (imgX >= 0 && imgX < width && imgY >= 0 && imgY < height) {
                            const offset = (imgY * width + imgX) * 4;
                            const weight = this.kernel[ky * kernelSize + kx];
                            sumR += data[offset] * weight;
                            sumG += data[offset + 1] * weight;
                            sumB += data[offset + 2] * weight;
                        }
                    }
                }
                const offset = (y * width + x) * 4;
                outputData[offset] = Math.min(255, Math.max(0, sumR));
                outputData[offset + 1] = Math.min(255, Math.max(0, sumG));
                outputData[offset + 2] = Math.min(255, Math.max(0, sumB));
                outputData[offset + 3] = data[offset + 3]; // Alpha channel
            }
        }

        return new ImageData(outputData, width, height);
    }

}

// Создаем класс для обработки изображений
class ImageProcessor {
    constructor() {
        this.filters = {
            blur: [
                1 / 9, 1 / 9, 1 / 9,
                1 / 9, 1 / 9, 1 / 9,
                1 / 9, 1 / 9, 1 / 9
            ],
            edgeDetection: [
                -1, -1, -1,
                -1, 8, -1,
                -1, -1, -1
            ],
            sharpen: [
                0, -1, 0,
                -1, 5, -1,
                0, -1, 0
            ]
            // Добавьте другие фильтры по желанию
        };
    }

    applyFilter(filterName, imageData) {
        const filter = new ConvolutionFilter(this.filters[filterName]);
        return filter.apply(imageData);
    }
    applyCustomFilter(coefficients, imageData) {
        // Преобразуем каждое значение в число
        const parsedCoefficients = coefficients.map(Number);

        // Проверяем, нужна ли нормализация коэффициентов
        const sum = parsedCoefficients.reduce((acc, curr) => acc + curr, 0);
        const needNormalization = Math.abs(sum - 1) > Number.EPSILON;

        // Нормализуем коэффициенты, если это необходимо
        const normalizedCoefficients = needNormalization ? parsedCoefficients.map(coef => coef / sum) : parsedCoefficients;

        // Применяем фильтр с нормализованными или исходными коэффициентами
        const filter = new ConvolutionFilter(normalizedCoefficients);
        return filter.apply(imageData);
    }

}

