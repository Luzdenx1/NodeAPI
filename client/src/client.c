#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();
    if (logger == NULL) {
        printf("%s","No se pudo crear el logger");
        return 0;
    }
    //log_info(logger,"Hola! Soy un Log");

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();
    if (config == NULL) {
        printf("%s","No se pudo encontrar el archivo de configuracion");
        return 0;
    }

    ip = config_get_string_value(config,"IP");
    puerto = config_get_string_value(config,"PUERTO");
    valor = config_get_string_value(config,"CLAVE");
    //log_info(logger, valor);

	/* ---------------- LEER DE CONSOLA ---------------- */

	//leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	conexion = crear_conexion(ip, puerto);

    enviar_mensaje(valor,conexion);

	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger = log_create( "tp0.log", "Client", false, LOG_LEVEL_INFO);

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config = config_create("../cliente.config") ;
	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	leido = readline("> ");
    while(strcmp(leido,"")!=0){
        log_info(logger, leido);
        leido = readline("> ");
    }
    free(leido);
}

void paquete(int conexion)
{
	char* leido = readline("> ");;
	t_paquete* paquete = crear_paquete();
    while(strcmp(leido,"")!=0){
        agregar_a_paquete(paquete,leido, string_length(leido));
        leido = readline("> ");
    }
    enviar_paquete(paquete,conexion);
    free(leido);
    eliminar_paquete(paquete);
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
	  log_destroy(logger);
      config_destroy(config);
      liberar_conexion(conexion);
}
