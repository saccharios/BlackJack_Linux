pipeline 
{
    agent 
    { 
	docker { image 'blackjack:latest' }
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
	stage('build')
	{
	    steps
	    {
               sh 'scons Simulations'
	    }
	}
    }
}
