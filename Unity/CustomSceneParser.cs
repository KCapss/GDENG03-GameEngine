using System.Collections;
using System.Collections.Generic;


using UnityEngine;
using UnityEditor;
using System.IO;


[CustomEditor(typeof(LevelLoader))]
public class CustomSceneParser : Editor
{
    public override void OnInspectorGUI()
    {
        DrawDefaultInspector();
        LevelLoader myScript = (LevelLoader)target;

        if (GUILayout.Button("Generate Scenes"))
        {
            //LevelLoader.ReadString();
            myScript.ParseReading();
        }
    }
}

[CustomEditor(typeof(RigidBodySpawner))]
public class CustomSpawner : Editor
{

    public override void OnInspectorGUI()
    {
        DrawDefaultInspector();
        RigidBodySpawner myScript = (RigidBodySpawner)target;

        if (GUILayout.Button("Batch Spawn"))
        {
            myScript.SpawnBatchRigidBodies();
        }

        if (GUILayout.Button("Clear Batch Spawn"))
        {
            myScript.ClearGameObject();
        }
    }

}
