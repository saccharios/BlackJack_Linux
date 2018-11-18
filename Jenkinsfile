pipeline 
{
    agent 
    { 
	docker { image 'my_setup:latest' }
    }
    stages 
    {
        stage('pyhton version')
        {
            steps 
            {
                sh 'python --version'
            }
        }
	stage('build')
	{
	    steps
	    {
               sh 'scons Simulations'
	    }
	}
    }
}
