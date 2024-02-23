// Получаем ссылку на куб
const cube = document.querySelector('.cube');

// Функция для применения трансформаций
function applyTransformations() {
  cube.style.transform = `rotateX(${rotationX}deg) rotateY(${rotationY}deg)`;
}

// Инициализация углов поворота
let rotationX = 0;
let rotationY = 0;

// Применяем начальные трансформации
applyTransformations();

// Обработчик событий для перемещения мыши
document.addEventListener('mousemove', function(event) {
  const { clientX, clientY } = event;
  const centerX = window.innerWidth / 2;
  const centerY = window.innerHeight / 2;
  rotationY = (clientX - centerX) / 10;
  rotationX = (clientY - centerY) / 10;
  applyTransformations();
});


