
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

void LoadLevelParse(int32 currentLevel)
{
	DynamicArray<TokenVal> tokens = MakeDynamicArray<TokenVal>(&Game->frameMem, 10000);
	DynamicArray<Wall> walls = MakeDynamicArray<Wall>(&Game->frameMem, 10000);

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

			while (isDigit(c))
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
									if (w.modelRenderData.position.x == NULL)
									{
										w.modelRenderData.position.x = strtoll(t.start, NULL, 10);
									} 
									else if (w.modelRenderData.position.y == NULL)
									{
										w.modelRenderData.position.y = strtoll(t.start, NULL, 10);
									} 
									else if (w.modelRenderData.position.z == NULL)
									{
										w.modelRenderData.position.z = strtoll(t.start, NULL, 10);
									}

									tokenIndex++;
									t = tokens[tokenIndex];

								}
								if (t.type == TokenType_Comma)
								{
									tokenIndex++;
									t = tokens[tokenIndex];
								}

								/*if (t.type == TokenType_RightParen)
								{
									tokenIndex++;
									t = tokens[tokenIndex];
								}*/
							}
							tokenIndex++;
							t = tokens[tokenIndex];
						}
						PushBack(&walls, w);
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
}


void SaveAndWriteLevel()
{

	FileHandle file;

	char* path[] =
	{
	   "data/levelEditor/level0.txt",
	   "data/levelEditor/level1.txt",
	   "data/levelEditor/level2.txt",
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
		char posToken[10] = "#pos\n";
		char sizeToken[12] = "#size\n";
		

		for (int i = 0; i < terrainBuffer->count; i++)
		{
		}

		for (int i = 0; i < wallBuffer->count; i++)
		{
		}
	}

	CloseFile(&file);
}