pipeline 
{
    agent 
    { 
		dockerfile
		{
			filename 'Dockerfile'
		}	
    }
    stages 
    {
        stage('pyhton version')
        {
            steps 
            {
                sh 'python --version'
                sh 'scons --version'
            }
        }
	stage('build scons Simulations')
	{
	    steps
	    {
               sh 'scons Simulations'
	    }
	}
    }
}
