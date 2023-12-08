using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RigidBodySpawner : MonoBehaviour
{
    private List<GameObject> gameObjectList = new List<GameObject>();

    public void SpawnBatchRigidBodies()
    {

        for (int i = 0; i < 20; i++)
        {
            GameObject gameObjectCopy = GameObject.CreatePrimitive(PrimitiveType.Cube);

            if (i != 0)
            {
                gameObjectCopy.name = $"Physics Cube ({i})";

            }

            else
            {
                gameObjectCopy.name = "Physics Cube";
            }


            //Add Transform
            gameObjectCopy.transform.position = new Vector3(
                Random.Range(-8.0f, 8.0f),
                Random.Range(1.0f, 8.0f),
                Random.Range(-8.0f, 8.0f)
            );
            gameObjectCopy.transform.rotation = Quaternion.Euler(new Vector3(
                Random.Range(-180.0f, 180.0f),
                Random.Range(-180.0f, 180.0f),
                Random.Range(-180.0f, 180.0f)
                ));

            //gameObjectCopy.transform.rotation.SetEulerAngles(new Vector3(
            //        Random.Range(-180.0f, 180.0f),
            //        Random.Range(-180.0f, 180.0f),
            //        Random.Range(-180.0f, 180.0f)
            //    )
            //);

            //Rigid Body
            Rigidbody rb = gameObjectCopy.AddComponent<Rigidbody>();
            rb.mass = 1.0f;
            rb.useGravity = true;

        }
    }

    public void ClearGameObject()
    {
        foreach (GameObject gameObject in gameObjectList)
        {
            DestroyImmediate(gameObject);
        }

        gameObjectList.Clear();
    }
}


