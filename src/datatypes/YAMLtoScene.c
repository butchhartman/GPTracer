#include "YAMLtoScene.h"

void yaml_nextEvent(yaml_parser_t *parser, yaml_event_t *event) {
    yaml_event_delete(event);
    yaml_parser_parse(parser, event);
}

void yaml_parseScene(World *world, const char *path) {
	FILE *fh = fopen(path, "r");
	yaml_parser_t parser;
	yaml_event_t event = {0};


	if(!yaml_parser_initialize(&parser)) {
		printf("Failed to initialize parser\n");
	}
	if (fh == NULL) {
		printf("Failed to open yaml file\n");
	}

	yaml_parser_set_input_file(&parser, fh);

	while (event.type != YAML_STREAM_END_EVENT) {

		if (!yaml_parser_parse(&parser, &event)) {
			printf("Parsor error %d\n", parser.error);
			exit(EXIT_FAILURE);
		}

		switch (event.type) {
			case YAML_STREAM_START_EVENT: printf("STREAM START\n"); break;
			case YAML_STREAM_END_EVENT: printf("STREAM END\n"); break;

			case YAML_DOCUMENT_START_EVENT: printf("\tStart Document\n"); break;
			case YAML_DOCUMENT_END_EVENT: printf("\tEnd Document\n"); break;
			
			case YAML_SEQUENCE_START_EVENT: printf("\t\tStart Sequence\n"); break;
			case YAML_SEQUENCE_END_EVENT: printf("\t\tEnd Sequence\n"); break;

			case YAML_MAPPING_START_EVENT: printf("\t\t\tStart Mapping\n"); break;
			case YAML_MAPPING_END_EVENT: printf("\t\t\tEnd Mapping\n"); break;

			case YAML_ALIAS_EVENT: printf("\t\t\t\tGot alias (anchor %s)\n", event.data.alias.anchor); break;
			case YAML_SCALAR_EVENT: printf("\t\t\t\tGot scalar (value %s)\n", event.data.scalar.value); 

                    if (strcmp(event.data.scalar.value, "add") == 0) {
                        // When the add event is called, get the next scalar and check what needs to be added
                        yaml_nextEvent(&parser, &event);
                        printf("event after add : %s", event.data.scalar.value);

                        if (strcmp(event.data.scalar.value, "light") == 0) {
                            Pointlight plight = pointlight_createPointlight(tuple_createPoint(0, 0, 0), tuple_createColor(0, 0, 0));

                            yaml_nextEvent(&parser, &event);

                            if (strcmp(event.data.scalar.value, "at") == 0) {
                                yaml_nextEvent(&parser, &event); // For some magical fucking reason, there must be two event swap calls to access the values after at. I assume it has something to do with them being in a separate sequence or something
                                yaml_nextEvent(&parser, &event);
                                plight.position.x = atof(event.data.scalar.value);
                                yaml_nextEvent(&parser, &event);
                                plight.position.y = atof(event.data.scalar.value);
                                yaml_nextEvent(&parser, &event);
                                plight.position.z = atof(event.data.scalar.value);
                            }

                            yaml_nextEvent(&parser, &event); // to and from each array of values, a double is needed
                            yaml_nextEvent(&parser, &event);
                            if (strcmp(event.data.scalar.value, "intensity") == 0) {
                                yaml_nextEvent(&parser, &event); // to and from each array of values, a double is needed
                                yaml_nextEvent(&parser, &event);
                                plight.intensity.x = atof(event.data.scalar.value);
                                yaml_nextEvent(&parser, &event);
                                plight.intensity.y = atof(event.data.scalar.value);
                                yaml_nextEvent(&parser, &event);
                                plight.intensity.z = atof(event.data.scalar.value);
                            }

                            world->light = plight; 
                        }
                        

                    }

            break;
		}



		if (event.type != YAML_STREAM_END_EVENT) {
			yaml_event_delete(&event);
		}

	}
	yaml_event_delete(&event);

	yaml_parser_delete(&parser);
	fclose(fh);
}
