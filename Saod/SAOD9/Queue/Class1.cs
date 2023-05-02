



    struct Person
    {
        public string name;
        public char sex; // 'F' (женщина) ; 'M' (мужчина)
    }

    class DancePartners
    {
        static void Main(string[] args)
        {
            // две очереди для разделения на партнеров по танцу 
            Queue<Person> maleDancers = new Queue<Person>();
            Queue<Person> femaleDancers = new Queue<Person>();
            Person p;
            char blankseparator;

            // входной файл для танцоров 
            StreamReader fin = new StreamReader("dance.dat");
            if (fin == null)
            {
                Console.WriteLine("He возможно открыть файл!");
                Environment.Exit(1);
            }

            // считать входную строку, которая включает пол, имя и возраст 
            while (!fin.EndOfStream)
            {
                p.sex = (char)fin.Read();
                blankseparator = (char)fin.Read();
                p.name = fin.ReadLine();
                // вставить в соответствующую очередь 
                if (p.sex == 'F')
                {
                    femaleDancers.Enqueue(p);
                }
                else
                {
                    maleDancers.Enqueue(p);
                }
            }

            // установить пару танцоров, получением партнеров
            // из двух очередей 
            // закончить, когда одна из очередей окажется пустой 
            Console.WriteLine("Партнеры по танцу: \n");
            while (femaleDancers.Count > 0 && maleDancers.Count > 0)
            {
                p = femaleDancers.Dequeue();
                Console.Write(p.name + " "); // сообщить имя женщины 
                p = maleDancers.Dequeue();
                Console.Write(p.name + "\n"); // сообщить имя мужчины
                Console.WriteLine();

                // если в какой-либо очереди кто-либо остался,
                // сообщить имя первого (первой) из них 
                if (femaleDancers.Count > 0)
                {
                    Console.WriteLine("Следующего танца ожидают " + femaleDancers.Count + " дамы");
                    Console.WriteLine(femaleDancers.Peek().name + " первой получит партнера.\n");
                }
                else if (maleDancers.Count > 0)
                {
                    Console.WriteLine("Следующего танца ожидают " + maleDancers.Count + " кавалера");
                    Console.WriteLine(maleDancers.Peek().name + " первым получит партнера.\n");
                }
            }

            fin.Close();
        }
    }


