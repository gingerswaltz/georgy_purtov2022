
public class PostfixCalculator
{


    public static double Calculate(string expression)
    {
        Stack<double> stack = new Stack<double>(); // Создаем экземпляр класса Stack для хранения чисел

        foreach (string token in expression.Split(' ')) // Разбиваем выражение на токены и перебираем их
        {
            if (double.TryParse(token, out double number)) // Если токен является числом
            {
                stack.Push(number); // Добавляем число на вершину стэка
            }
            else // Иначе, токен является оператором
            {
                double operand2 = stack.Pop(); // Извлекаем из стэка второй операнд
                double operand1 = stack.Pop(); // Извлекаем из стэка первый операнд

                switch (token) // Выполняем операцию в зависимости от оператора
                {
                    case "+":
                        stack.Push(operand1 + operand2); // Добавляем результат операции на вершину стэка
                        break;
                    case "-":
                        stack.Push(operand1 - operand2); // Добавляем результат операции на вершину стэка
                        break;
                    case "*":
                        stack.Push(operand1 * operand2); // Добавляем результат операции на вершину стэка
                        break;
                    case "/":
                        stack.Push(operand1 / operand2); // Добавляем результат операции на вершину стэка
                        break;
                    default:
                        throw new ArgumentException($"Invalid operator: {token}"); // Если оператор недопустим, выбрасываем исключение
                }
            }
        }

        if (stack.Count() != 1) // Если в стэке осталось больше одного элемента
        {
            throw new ArgumentException("Invalid expression"); // Выражение неверно
        }

        return stack.Pop(); // Возвращаем результат вычислений
    }
}
class Program
{
    static void Main(string[] args)
    {
        Console.WriteLine("Enter a postfix expression:"); // 7 2 3 * - == 1
        string expression = Console.ReadLine(); // Считываем постфиксное выражение из консоли

        try
        {
            double result = PostfixCalculator.Calculate(expression); // Вычисляем значение выражения

            Console.WriteLine($"Result: {result}"); // Выводим результат
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error: {ex.Message}"); // Выводим сообщение об ошибке, если возникла исключительная ситуация
        }

        Console.ReadKey(); // Ждем, пока пользователь нажмет любую клавишу, чтобы закрыть консоль
    }
}





