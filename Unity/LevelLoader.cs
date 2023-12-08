using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using UnityEngine;
using System.IO;
using Unity.VisualScripting;
using Debug = UnityEngine.Debug;

public class RigidBodyProperties
{
    // First Row
    public string name;

    // Second Row
    public int objectType = 0;
    public bool isRigidPresent = false;
    public float mass = 0.0f;
    public bool isGravityEnabled = true;

    //Third Row - Last
    public Vector3 position = new Vector3(0, 0, 0);
    public Vector3 rotation = new Vector3(0, 0, 0);
    public Vector3 scale = new Vector3(0, 0, 0);

    public RigidBodyProperties()
    {
    }

    public void ClearSettings()
    {
        isRigidPresent = false;
    }

};

public class LevelLoader : MonoBehaviour
{
    public  enum OBJECTPROPERTIES{
        Name = 0,
        RigidBodies = 1,
        Position = 2,
        Rotation = 3,
        Scale = 4
    }

   
    [SerializeField] private String filePath;
    private string defaultfileExtension = ".level";

    private  RigidBodyProperties gameObjectProperties;
    

    public void ReadString()
    {
        String path = filePath;
        StreamReader reader = new StreamReader(path);
        Debug.Log(reader.ReadToEnd());
        reader.Close();
    }


    public void ParseReading()
    {
        gameObjectProperties = new RigidBodyProperties();

        string path = filePath;
        StreamReader reader = new StreamReader(path);
        string line;
        //Splitting Per Line
        char[] delimiterChars = { ' ', '|' };

        int i = 0; //Per each line
        while ((line = reader.ReadLine()) != null)
        {
            if (i == 0)
            {
                UpdateProperties(line, (OBJECTPROPERTIES)i);
                i++;
            }
            
            else
            {
                UpdateProperties(line, (OBJECTPROPERTIES)i);
                if (i == 4)
                {
                    //Spawn Something
                    ConstructGameObject();
                    i = 0;

                }

                else
                {
                    i++;
                }
            }

           
        }

        Debug.Log("Done");
    }

    private void UpdateProperties(string line, OBJECTPROPERTIES types )
    {
        char[] delimiterChars = { ' ',  '|' };
        string[] stringSection = line.Split(delimiterChars);
           
            {
                switch (types)
                {
                    case OBJECTPROPERTIES.Name:
                        gameObjectProperties.name = line;
                    break;

                    case OBJECTPROPERTIES.RigidBodies: //Rigid Body
                        gameObjectProperties.objectType = int.Parse(stringSection[1]);
                        Debug.Log($"Type: {gameObjectProperties.objectType}");
                        gameObjectProperties.isRigidPresent = int.Parse(stringSection[2]) == 1;
                        gameObjectProperties.mass = float.Parse(stringSection[3]);
                        gameObjectProperties.isGravityEnabled = int.Parse(stringSection[4]) == 1;

                        break;

                    case OBJECTPROPERTIES.Position: //Position
                        gameObjectProperties.position.x = float.Parse(stringSection[1]);
                        gameObjectProperties.position.y = float.Parse(stringSection[2]);
                        gameObjectProperties.position.z = float.Parse(stringSection[3]);
                    break;

                    case OBJECTPROPERTIES.Rotation: //Rotation

                        //Converting it into degrees first
                        gameObjectProperties.rotation.x = float.Parse(stringSection[1]) * (180.0f / (float)Math.PI);
                        gameObjectProperties.rotation.y = float.Parse(stringSection[2]) * (180.0f / (float)Math.PI);
                        gameObjectProperties.rotation.z = float.Parse(stringSection[3]) * (180.0f / (float)Math.PI);
                        
                    break;

                    case OBJECTPROPERTIES.Scale: //Rigid Body
                        gameObjectProperties.scale.x = float.Parse(stringSection[1]);
                        gameObjectProperties.scale.y = float.Parse(stringSection[2]);
                        gameObjectProperties.scale.z = float.Parse(stringSection[3]);
                    break;
                }
            }

    }

    private void ConstructGameObject()
    {
        GameObject gameObjectCopy = new GameObject();
            //= new GameObject();
      

        //First Identify the Game Object Type
        switch (gameObjectProperties.objectType)
        {
            
            case 0: //Cube
                DestroyImmediate(gameObjectCopy);
                gameObjectCopy = GameObject.CreatePrimitive(PrimitiveType.Cube);
                break;

            case 1: //Physics Cube
                DestroyImmediate(gameObjectCopy);
                gameObjectCopy = GameObject.CreatePrimitive(PrimitiveType.Cube);
                break;

            case 2: //Plane
                DestroyImmediate(gameObjectCopy);
                gameObjectCopy = GameObject.CreatePrimitive(PrimitiveType.Plane);
                gameObjectProperties.scale = gameObjectProperties.scale / 10.0f;
                //gameObjectProperties.rotation.x += 90.0f;
                break;

            case 3: //Physics Plane
                DestroyImmediate(gameObjectCopy);

                gameObjectCopy = GameObject.CreatePrimitive(PrimitiveType.Cube);
                break;
        }

        //Changing the Transformation Component
        gameObjectCopy.GetComponent<Transform>().position = gameObjectProperties.position;
        Quaternion rotationQuaternion = new Quaternion();
        rotationQuaternion = Quaternion.Euler(gameObjectProperties.rotation);
        gameObjectCopy.GetComponent<Transform>().rotation = rotationQuaternion;
        gameObjectCopy.GetComponent<Transform>().localScale = gameObjectProperties.scale;

        //Checking for rigidBody Component
        if (gameObjectProperties.isRigidPresent)
        {
            Rigidbody rigidbody = gameObjectCopy.AddComponent<Rigidbody>();

            if (gameObjectProperties.objectType >= 2)
                rigidbody.isKinematic = true;

            rigidbody.useGravity = gameObjectProperties.isGravityEnabled;
            rigidbody.mass = gameObjectProperties.mass;
        }

        gameObjectCopy.name = gameObjectProperties.name;

        //Instantiate(gameObjectCopy);
        gameObjectProperties.ClearSettings();
    }

    
}
