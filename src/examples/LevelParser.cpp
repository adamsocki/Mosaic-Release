
bool isLetter(char c)
{
	return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}
bool isDigit(char c)
{
	return c >= '0' && c <= '9';
}
bool isPeriod(char c)
{
	return c == '.';
}
bool isComma(char c)
{
	return c == ',';
}
bool isNeg(char c)
{
	return c == '-';
}

void LoadLevelParse(int32 currentLevel)
{
	DynamicArray<TokenVal> tokens = MakeDynamicArray<TokenVal>(&Game->frameMem, 10000);
	DynamicArray<Wall> walls = MakeDynamicArray<Wall>(&Game->frameMem, 10000);
	DynamicArray<Door> doors = MakeDynamicArray<Door>(&Game->frameMem, 10000);

	FileHandle file;

	char* path[] =
	{
	   "data/levelFiles/level0.txt",
	   "data/levelEditor/level1.txt",
	   "data/levelEditor/level2.txt"
	};

	// boiler plate code
	if (OpenFileForRead(path[currentLevel], &file, &Game->frameMem))
	{
		TokenVal t = {};
		while (file.offset < file.size)
		{
			t = {};
			char c = ReadChar(&file);

			while (c == ' ' || c == '\n' || c == '\r') {
				goto Advance;
			}
			
			if (c == '$')
			{
				t.start = (char*)&file.data[file.offset - 1];
				t.length = 1;
				t.type = TokenType_DollarSymb;
				goto AddToken;
			}

			while (isLetter(c))
			{
				if (t.start == NULL)
				{
					t.type = TokenType_Identifier;
					t.start = (char*)&file.data[file.offset - 1];
					//t.length = 1;
				}

				t.length++;

				char nextChar = file.data[file.offset];
				if (!isLetter(nextChar))
				{
					goto AddToken;
					break;
				}
				else
				{
					c = ReadChar(&file);
				}

			}

			if (c == '(')
			{
				t.start = (char*)&file.data[file.offset - 1];
				t.length = 1;
				t.type = TokenType_LeftParen;
			}

			if (c == ')')
			{
				t.start = (char*)&file.data[file.offset - 1];
				t.length = 1;
				t.type = TokenType_RightParen;
			}
			if (c == ',')
			{
				t.type = TokenType_Comma;
				t.start = (char*)&file.data[file.offset - 1];
				t.length = 1;
			}

			while (isDigit(c) || isNeg(c))
			{
				if (t.start == NULL)
				{
					t.type = TokenType_Integer;
					t.start = (char*)&file.data[file.offset - 1];
				}
				t.length++;
				char nextChar = file.data[file.offset];
				if (!isDigit(nextChar))
				{
					goto AddToken;
					break;
				}
				else
				{
					c = ReadChar(&file);
				}
			}

			if (c == '#')
			{
				t.start = (char*)&file.data[file.offset - 1];
				t.type = TokenType_PoundSymb;
				t.length = 1;
			}

			if (c == '@')
			{
				t.start = (char*)&file.data[file.offset - 1];
				t.type = TokenType_End;
				t.length = 1;
			}

		AddToken:
			PushBack(&tokens, t);

		Advance:
			int32 baba = 0;

		}
		CloseFile(&file);
	}

	//	READ DEM TOKEs
	int32 tokenIndex = 0;
	while (tokenIndex < tokens.count)
	{
		TokenVal t = tokens[tokenIndex];

		if (t.type == TokenType_DollarSymb)
		{
			tokenIndex++;
			t = tokens[tokenIndex];

			if (t.type == TokenType_Identifier)
			{
				if (strncmp(t.start, "wall", t.length) == 0)
				{
					tokenIndex++;
					t = tokens[tokenIndex];

					Wall w = {};
					// CREATE WALL ENTITY
					while (t.type == TokenType_PoundSymb)
					{
						tokenIndex++;
						t = tokens[tokenIndex];
						bool xPosAdded = false;
						bool yPosAdded = false;
						bool zPosAdded = false;
						bool xScaleAdded = false;
						bool yScaleAdded = false;
						bool zScaleAdded = false;

						// GATHER WALL POSITION
						if (strncmp(t.start, "pos", t.length) == 0)
						{
							tokenIndex++;
							t = tokens[tokenIndex];

							// LOOP OVER UNTIL DONE WITH POSITIONS
							while (t.type != TokenType_RightParen)
							{
								tokenIndex++;
								t = tokens[tokenIndex];
								vec2 position;
								if (t.type == TokenType_Integer)
								{
									if (!xPosAdded)
									{
										xPosAdded = true;
										w.modelRenderData.position.x = strtoll(t.start, NULL, 10);
									} 
									else if (!yPosAdded)
									{
										yPosAdded = true;
										w.modelRenderData.position.y = strtoll(t.start, NULL, 10);
									} 
									else if (!zPosAdded)
									{
										zPosAdded = true;
										w.modelRenderData.position.z = strtoll(t.start, NULL, 10);
									}
								}
							}
							tokenIndex++;
							t = tokens[tokenIndex];
						}
						tokenIndex++;
						t = tokens[tokenIndex];
						if (strncmp(t.start, "scale", t.length) == 0)
						{
							tokenIndex++;
							t = tokens[tokenIndex];

							// LOOP OVER UNTIL DONE WITH POSITIONS
							while (t.type != TokenType_RightParen)
							{
								tokenIndex++;
								t = tokens[tokenIndex];
								vec2 position;
								if (t.type == TokenType_Integer)
								{
									if (!xScaleAdded)
									{
										xScaleAdded = true;
										w.modelRenderData.scale.x = strtoll(t.start, NULL, 10);
									}
									else if (!yScaleAdded)
									{
										yScaleAdded = true;
										w.modelRenderData.scale.y = strtoll(t.start, NULL, 10);
									}
									else if (!zScaleAdded)
									{
										zScaleAdded = true;
										w.modelRenderData.scale.z = strtoll(t.start, NULL, 10);
									}
								}
							}
							tokenIndex++;
							t = tokens[tokenIndex];
						}
						tokenIndex++;
						t = tokens[tokenIndex];
						if (strncmp(t.start, "roomNum", t.length) == 0)
						{
							tokenIndex++;
							t = tokens[tokenIndex];

							w.modelRenderData.roomNum = strtoll(t.start, NULL, 10);

							tokenIndex++;
							t = tokens[tokenIndex];
						}
						PushBack(&walls, w);
					}
				}
				if (strncmp(t.start, "door", t.length) == 0)
				{
					tokenIndex++;
					t = tokens[tokenIndex];

					Door d = {};
					// CREATE DOOR ENTITY
					while (t.type == TokenType_PoundSymb)
					{
						tokenIndex++;
						t = tokens[tokenIndex];
						bool xPosAdded = false;
						bool yPosAdded = false;
						bool zPosAdded = false;
						bool xScaleAdded = false;
						bool yScaleAdded = false;
						bool zScaleAdded = false;

						// GATHER DOOR POSITION
						if (strncmp(t.start, "pos", t.length) == 0)
						{
							tokenIndex++;
							t = tokens[tokenIndex];

							// LOOP OVER UNTIL DONE WITH POSITIONS
							while (t.type != TokenType_RightParen)
							{
								tokenIndex++;
								t = tokens[tokenIndex];
								vec2 position;
								if (t.type == TokenType_Integer)
								{
									if (!xPosAdded)
									{
										xPosAdded = true;
										d.modelRenderData.position.x = strtoll(t.start, NULL, 10);
									}
									else if (!yPosAdded)
									{
										yPosAdded = true;
										d.modelRenderData.position.y = strtoll(t.start, NULL, 10);
									}
									else if (!zPosAdded)
									{
										zPosAdded = true;
										d.modelRenderData.position.z = strtoll(t.start, NULL, 10);
									}
								}
							}
							tokenIndex++;
							t = tokens[tokenIndex];
						}
						tokenIndex++;
						t = tokens[tokenIndex];
						if (strncmp(t.start, "scale", t.length) == 0)
						{
							tokenIndex++;
							t = tokens[tokenIndex];

							// LOOP OVER UNTIL DONE WITH POSITIONS
							while (t.type != TokenType_RightParen)
							{
								tokenIndex++;
								t = tokens[tokenIndex];
								vec2 position;
								if (t.type == TokenType_Integer)
								{
									if (!xScaleAdded)
									{
										xScaleAdded = true;
										d.modelRenderData.scale.x = strtoll(t.start, NULL, 10);
									}
									else if (!yScaleAdded)
									{
										yScaleAdded = true;
										d.modelRenderData.scale.y = strtoll(t.start, NULL, 10);
									}
									else if (!zScaleAdded)
									{
										zScaleAdded = true;
										d.modelRenderData.scale.z = strtoll(t.start, NULL, 10);
									}
								}
							}
							tokenIndex++;
							t = tokens[tokenIndex];
						}
						tokenIndex++;
						t = tokens[tokenIndex];
						if (strncmp(t.start, "roomNum", t.length) == 0)
						{
							tokenIndex++;
							t = tokens[tokenIndex];

							d.modelRenderData.roomNum = strtoll(t.start, NULL, 10);

							tokenIndex++;
							t = tokens[tokenIndex];
						}
						PushBack(&doors, d);
					}
				}
			}
		}
		else
		{
			tokenIndex++;
			t = tokens[tokenIndex];
		}
	}

	EntityTypeBuffer* wallBuffer = &Data->em.buffers[EntityType_Wall];
	Wall* wallEntitiesInBuffer = (Wall*)wallBuffer->entities;

	for (int i = 0; i < walls.count; i++)
	{
		EntityHandle wallHandle = AddEntity(&Data->em, EntityType_Wall);
		Wall* wallEntity = (Wall*)GetEntity(&Data->em, wallHandle);
		wallEntity->handle = wallHandle;
		wallEntity->modelRenderData.position = walls[i].modelRenderData.position;
		wallEntity->modelRenderData.scale = walls[i].modelRenderData.scale;

	}

	DeallocateDynamicArray(&tokens);
	DeallocateDynamicArray(&walls);
	DeallocateDynamicArray(&doors);
}

int getSize(char* s) {
	char* t; // first copy the pointer to not change the original
	int size = 0;

	for (t = s; *t != '\0'; t++) {
		size++;
	}

	return size;
}

void WriteValues(char* val, FileHandle* file)
{
	for (int i = 0; i < getSize(val); i++) {

		WriteByte(file, (u8)val[i]);
	}
}

void SaveAndWriteLevel()
{

	FileHandle file;

	char* path[] =
	{
	   "data/levelFiles/level0.txt",
	   "data/levelFiles/level1.txt",
	   "data/levelFiles/level2.txt",
	};
	if (OpenFileForWrite(path[Data->le.currentLevel], &file, &Game->frameMem, sizeof(Entity) * 10000))
	{
		EntityTypeBuffer* terrainBuffer = &Data->em.buffers[EntityType_Terrain];
		Terrain* terrainEntitiesInBuffer = (Terrain*)terrainBuffer->entities;

		EntityTypeBuffer* wallBuffer = &Data->em.buffers[EntityType_Wall];
		Wall* wallEntitiesInBuffer = (Wall*)wallBuffer->entities;


		
		char leftParen[2] = "(";
		char rightParen[2] = ")";
		char comma[2] = ",";
		char newLine[3] = "\n";
		char end[3] = "@";
		char posToken[10] = "#pos\n";
		char scaleToken[12] = "#scale\n";
		char roomNumToken[12] = "#roomNum\n";
		

		for (int i = 0; i < terrainBuffer->count; i++)
		{
		}

		/*for (int i = 0; i < postBuffer->count; i++)
		{

		}*/

		for (int i = 0; i < wallBuffer->count; i++)
		{
			Wall* wallEntity = (Wall*)GetEntity(&Data->em, wallEntitiesInBuffer[i].handle);
			char typeName[10] = "$wall\n";
			char pos_x[5];
			char pos_y[5];
			char pos_z[5];
			char scale_x[5];
			char scale_y[5];
			char scale_z[5];
			char roomNum[5];


			sprintf(pos_x, "%.0f", wallEntity->modelRenderData.position.x);
			sprintf(pos_y, "%.0f", wallEntity->modelRenderData.position.y);
			sprintf(pos_z, "%.0f", wallEntity->modelRenderData.position.z);
			sprintf(scale_x, "%.0f", wallEntity->modelRenderData.scale.x);
			sprintf(scale_y, "%.0f", wallEntity->modelRenderData.scale.y);
			sprintf(scale_z, "%.0f", wallEntity->modelRenderData.scale.z);
			sprintf(roomNum, "%d", wallEntity->modelRenderData.roomNum);

			WriteValues(typeName, &file);
			WriteValues(posToken, &file);
			WriteValues(leftParen, &file);
			WriteValues(pos_x, &file);
			WriteValues(comma, &file);
			WriteValues(pos_y, &file);
			WriteValues(comma, &file);
			WriteValues(pos_x, &file);
			WriteValues(rightParen, &file);
			WriteValues(newLine, &file);

			WriteValues(scaleToken, &file);
			WriteValues(leftParen, &file);
			WriteValues(scale_x, &file);
			WriteValues(comma, &file);
			WriteValues(scale_y, &file);
			WriteValues(comma, &file);
			WriteValues(scale_z, &file);
			WriteValues(rightParen, &file);
			WriteValues(newLine, &file);

			WriteValues(roomNumToken, &file);
			WriteValues(roomNum , &file);
			WriteValues(newLine, &file);

			WriteValues(newLine, &file);
			WriteValues(newLine, &file);
		}
		WriteValues(end, &file);
	}

	CloseFile(&file);
}