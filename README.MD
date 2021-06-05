# ARDUINO DATA LOGGER 

Sistema de coleta de dados de temperatura e umidade.

O sistema utiliza um módulo de controle para 3 módulos de sensores, cada controlador gravando os dados em um cartão micro-SD em intervalos predeterminados.

Os módulos de controle utilizam um Arduino UNO como controlador principal, sendo o master dos barramentos I2C de cada bloco de sensores.

## Componentes

Para os módulos de controle, foram utilizados:

 * 1 - [Arduino UNO REV3](https://www.eletrogate.com/uno-r3-cabo-usb-para-arduino)
 * 1 - [Módulo RTC DS1307](https://www.eletrogate.com/modulo-real-time-clock-ds1307)
 * 1 - [Módulo SD Card Reader](https://www.eletrogate.com/modulo-micro-sd-card)

Para os módulos de sensores, foram utilizados:

 * 1 - [Sensor de Temperatura e Umidade HDC1080](https://www.eletrogate.com/modulo-gy-213-sensor-de-temperatura-e-umidade-hdc1080)
 * 1 - [Sensor de Temperatura IR MLX90614](https://www.filipeflop.com/produto/sensor-de-temperatura-ir-mlx90614/)
 * 1 - [Sensor de Som KY-038](https://www.eletrogate.com/modulo-sensor-de-som)


