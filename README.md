**Projeto IoT com Comunicação TCP/IP e MQTT**


i) Descrição do Funcionamento e Uso:

Este projeto é um sistema de monitoramento de temperatura e umidade que utiliza um microcontrolador ESP8266 conectado a um sensor DHT11. Os dados coletados são enviados para um servidor MQTT (Message Queuing Telemetry Transport) e podem ser acessados remotamente via internet.

Para reproduzir o projeto, siga as instruções detalhadas abaixo. Primeiro, monte o hardware de acordo com as especificações fornecidas na seção de descrição do hardware. Em seguida, compile e carregue o software no microcontrolador ESP8266. Por fim, configure o servidor MQTT e conecte-se ao mesmo para visualizar os dados do sensor.

ii) Software Desenvolvido e Documentação de Código:

Configuração e Inicialização:

O código inicia declarando as bibliotecas necessárias para o funcionamento do dispositivo, incluindo a biblioteca DHT para o sensor DHT11, a biblioteca ESP8266WiFi para comunicação WiFi e a biblioteca ThingSpeak para comunicação MQTT.
São definidas as constantes para os pinos do sensor DHT11, as credenciais de rede WiFi e as informações do servidor MQTT (como endereço, porta, usuário e senha).
Na função setup(), o código inicia a comunicação serial para depuração, inicializa o sensor DHT11 e conecta-se à rede WiFi.

Leitura dos Sensores:

No loop principal (loop()), o código lê os dados de temperatura e umidade do sensor DHT11 utilizando as funções readTemperature() e readHumidity() da biblioteca DHT.
Os valores de temperatura e umidade são verificados para garantir que não são NaN (não-numéricos), o que indicaria uma falha na leitura do sensor.
Comunicação MQTT:

Após a leitura bem-sucedida dos sensores, os valores de temperatura e umidade são publicados no servidor MQTT utilizando a função publish().
Os dados são publicados em tópicos específicos, geralmente organizados hierarquicamente para facilitar a subscrição e o gerenciamento dos dados.

Comunicação TCP/IP e MQTT:

O dispositivo se conecta ao servidor MQTT através da conexão TCP/IP estabelecida pela biblioteca ESP8266WiFi. Isso permite que os dados sejam enviados e recebidos pela internet.
O protocolo MQTT é utilizado para a troca de mensagens entre o dispositivo e o servidor MQTT. Ele é leve e eficiente, adequado para dispositivos IoT com recursos limitados.

Manutenção da Conexão WiFi:

O código verifica continuamente o status da conexão WiFi. Se a conexão for perdida, o dispositivo tenta reconectar-se automaticamente à rede WiFi.
Depuração e Feedback:

O código utiliza a comunicação serial para fornecer feedback ao usuário durante a execução, exibindo mensagens de depuração, informações sobre a conexão WiFi e eventuais erros de leitura dos sensores ou falhas na comunicação MQTT.

iii) Descrição do Hardware Utilizado:

Para este projeto, você precisará dos seguintes componentes:

Microcontrolador ESP8266 NodeMCU
Sensor de temperatura e umidade DHT11
LEDs para indicadores visuais
Resistores para limitação de corrente dos LEDs
Placa de prototipagem
Fios jumper

iv) Documentação das Interfaces, Protocolos e Módulos de Comunicação:

A comunicação TCP/IP é estabelecida através do protocolo WiFi do ESP8266. Este protocolo permite que o microcontrolador se conecte à rede local e, posteriormente, à internet. O protocolo MQTT é usado para enviar e receber mensagens entre o ESP8266 e o servidor MQTT. Ele é ideal para comunicação entre dispositivos IoT devido à sua eficiência e baixo uso de largura de banda.

v) Comunicação/Controle via Internet e Uso do Protocolo MQTT:

Para configurar a comunicação via internet, você precisará fornecer as credenciais de rede WiFi no código-fonte do ESP8266. Isso permite que o dispositivo se conecte à sua rede local. Além disso, você precisará configurar um servidor MQTT, como o ThingSpeak, em uma máquina acessível pela internet. O ESP8266 deve ser configurado para se conectar a este servidor MQTT e publicar mensagens com os dados do sensor.
